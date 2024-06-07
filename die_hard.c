#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#define _(s) (s)

struct can
{
  long long unsigned int max_level;
  long long unsigned int level;
  int reservoir;
};

static int
can_cmp (const void *p1, const void *p2)
{
  struct can c1 = *(struct can *) p1;
  struct can c2 = *(struct can *) p2;

  if (c1.reservoir && !c2.reservoir)
    return 1;
  else if (!c1.reservoir && c2.reservoir)
    return -1;
  else if (c1.reservoir && c2.reservoir)
    return 0;
  else if (c1.max_level < c2.max_level)
    return -1;
  else if (c1.max_level > c2.max_level)
    return 1;
  else if (c1.level < c2.level)
    return -1;
  else if (c1.level > c2.level)
    return 1;
  else
    return 0;
}

struct set
{
  size_t nb_cans;
  struct can *cans;
};

static struct set *
set_create (size_t nb_cans, long long unsigned int *can_levels)
{
  struct set *s = malloc (sizeof (*s));
  s->nb_cans = nb_cans + 1;
  s->cans = calloc (s->nb_cans, sizeof (*s->cans));
  for (size_t i = 0; i < nb_cans; i++)
    s->cans[i].max_level = can_levels[i];
  s->cans[s->nb_cans - 1].reservoir = 1;
  return s;
}

static void
set_free (struct set *s)
{
  free (s->cans);
  free (s);
}

static void
set_print (const struct set *s)
{
  for (size_t c = 0; c < s->nb_cans; c++)
    if (!s->cans[c].reservoir)
      fprintf (stdout, _("{%1$llu/%2$llu} "), s->cans[c].level, s->cans[c].max_level);
}

static int
set_cmp (const void *p1, const void *p2)
{
  struct set s1 = *(struct set *) p1;
  struct set s2 = *(struct set *) p2;

  for (size_t i = 0; i < s1.nb_cans && i < s2.nb_cans; i++)
  {
    int cmp = can_cmp (s1.cans + i, s2.cans + i);
    if (cmp != 0)
      return cmp;
  }
  if (s1.nb_cans < s2.nb_cans)
    return -1;
  else if (s1.nb_cans > s2.nb_cans)
    return 1;
  else
    return 0;
}

static long long unsigned int
set_pour (const struct set *s, size_t from, size_t to)
{
  if (from >= s->nb_cans || to >= s->nb_cans || from == to)
    return 0;
  if (s->cans[from].reservoir && s->cans[to].reservoir)
    return 0;
  if (!s->cans[from].reservoir && s->cans[from].level == 0)
    return 0;
  if (!s->cans[to].reservoir && s->cans[to].max_level == s->cans[to].level)
    return 0;
  long long unsigned int poured = 0;
  if (s->cans[from].reservoir)
  {
    poured = s->cans[to].max_level - s->cans[to].level;
    s->cans[to].level = s->cans[to].max_level;
  }
  else if (s->cans[to].reservoir)
  {
    poured = s->cans[from].level;
    s->cans[from].level = 0;
  }
  else if (s->cans[from].level <= s->cans[to].max_level - s->cans[to].level)
  {
    poured = s->cans[from].level;
    s->cans[to].level += s->cans[from].level;
    s->cans[from].level = 0;
  }
  else                          // if (s->cans[from].level > s->cans[to].max_level - s->cans[to].level)
  {
    poured = s->cans[to].max_level - s->cans[to].level;
    s->cans[from].level -= s->cans[to].max_level - s->cans[to].level;
    s->cans[to].level = s->cans[to].max_level;
  }
  qsort (s->cans, s->nb_cans, sizeof (struct can), can_cmp);
  return poured;
}

struct ribbon
{
  struct elem
  {
    struct set *set;
    struct move
    {
      size_t depth;
      struct elem *prev;
      struct can *from, *to;
      long long unsigned int pour;
    } move;
    struct elem *next;
  } *begining, *end;
};

static void
ribbon_free (struct ribbon *r)
{
  struct elem *n;
  for (struct elem * e = r->begining; e; e = n)
  {
    set_free (e->set);
    n = e->next;
    free (e);
  }
  free (r);
}

static void
ribbon_elem_print (const struct elem *e)
{
  if (e->move.prev)
  {
    ribbon_elem_print (e->move.prev);
    if (!e->move.from->reservoir && !e->move.to->reservoir)
      fprintf (stdout, _("=(~%llu~>)=> "), e->move.pour);
    else if (e->move.from->reservoir && !e->move.to->reservoir)
      fprintf (stdout, _("=( ~>%llu)=> "), e->move.pour);
    else if (!e->move.from->reservoir && e->move.to->reservoir)
      fprintf (stdout, _("=(%llu~> )=> "), e->move.pour);
  }
  set_print (e->set);
}

static void
ribbon_add_set (struct ribbon *r, struct set *s, struct move move)
{
  qsort (s->cans, s->nb_cans, sizeof (struct can), can_cmp);
  struct elem *new = malloc (sizeof (*new));
  new->move = move;
  new->set = s;
  new->next = 0;
  if (r->end == 0)
    r->begining = new;
  else
    r->end->next = new;
  r->end = new;
}

static struct ribbon *
ribbon_create (size_t nb_cans, long long unsigned int *can_levels)
{
  struct set *s = set_create (nb_cans, can_levels);
  struct ribbon *r = calloc (1, sizeof (*r));
  ribbon_add_set (r, s, (struct move)
                  { 0, 0, 0, 0, 0 });
  return r;
}

static void
ribbon_feed (struct ribbon *r)
{
  size_t max = 0;
  for (size_t c = 0; c < r->begining->set->nb_cans; c++)
    max += r->begining->set->cans[c].max_level;
  struct elem **summary = calloc (max, sizeof (*summary));

  for (struct elem * e = r->begining; e; e = e->next)
  {
    int stop = 0;
    for (size_t pattern = 1; pattern < (1 << e->set->nb_cans); pattern++)
    {
      long long unsigned int sum = 0;
      for (size_t c = 0; c < e->set->nb_cans; c++)
        if ((1 << c) & pattern)
          sum += e->set->cans[c].level;
      if (sum && !summary[sum - 1])
      {
        summary[sum - 1] = e;
        stop = 1;
      }
    }
    for (size_t sum = 1; sum <= max && stop; sum++)
      if (!summary[sum - 1])
        stop = 0;
    if (stop)
      break;                    // for (struct elem * e = r->begining; e; e = e->next)
    for (size_t from = 0; from < e->set->nb_cans; from++)
      for (size_t to = 0; to < e->set->nb_cans; to++)
      {
        struct set *s = malloc (sizeof (*s));
        s->nb_cans = e->set->nb_cans;
        s->cans = malloc (s->nb_cans * sizeof (*s->cans));
        for (size_t i = 0; i < s->nb_cans; i++)
          s->cans[i] = e->set->cans[i];
        long long unsigned int pour = set_pour (s, from, to);
        if (pour)
        {
          int already = 0;
          for (struct elem * e2 = r->begining; e2 && !already; e2 = e2->next)
            if (set_cmp (s, e2->set) == 0)
              already = 1;
          if (!already)
          {
            ribbon_add_set (r, s, (struct move)
                            { e->move.depth + 1, e, &e->set->cans[from], &e->set->cans[to], pour });
            continue;           // for (from, to...
          }
        }
        set_free (s);
      }                         // for (from, to...
  }                             // for (struct elem * e = r->begining; e; e = e->next)

  for (size_t sum = 1; sum <= max; sum++)
    if (summary[sum - 1])
    {
      fprintf (stdout, _("The volume %1$zu is reachable in %2$zu moves: "), sum, summary[sum - 1]->move.depth);
      ribbon_elem_print (summary[sum - 1]);
      fprintf (stdout, "\n");
    }
    else
      fprintf (stdout, _("The volume %zu is not reachable.\n"), sum);
  free (summary);
}

int
main (int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf (stderr, _("Usage: %s volume [volume]...\n"), argv[0]);
    exit (-1);
  }

  long long unsigned int *can_levels = 0;
  size_t nb_cans = 0;
  for (int i = 1; i < argc; i++)
  {
    errno = 0;
    char *endptr;
    long long int l = strtoll (argv[i], &endptr, 0);
    if (!errno && endptr != argv[i] && *endptr == 0 && l > 0)
    {
      can_levels = reallocarray (can_levels, ++nb_cans, sizeof (*can_levels));
      can_levels[nb_cans - 1] = l;
    }
    else
    {
      fprintf (stderr, _("%1$s: \"%2$s\" is an invalid positive integer.\n"), argv[0], argv[i]);
      exit (-1);
    }
  }

  struct ribbon *Ribbon = ribbon_create (nb_cans, can_levels);
  free (can_levels);
  ribbon_feed (Ribbon);
  ribbon_free (Ribbon);
}
