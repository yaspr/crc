#include <stdio.h>

#include "types.h"
#include "crc.h"

u64 crc_table[256];

u64 rbit(u64 x, u64 len)
{
  u64 r = 0;

  for (u64 i = 0; i < len; i++)
    if ((x & (1ULL << i)))
      r |= ((1ULL << (len - i - 1)));
  
  return r;
}

void build_crc_table(crc_param_t *p, u64 m)
{
  u64 r = 0;

  for (u64 i = 0; i < 256; i++)
    {
      r = (p->rin) ? rbit(i, p->len) : (i << (p->len - 8));
      
      for (u64 j = 0; j < 8; j++)
	if (r & (1ULL << (p->len - 1)))
	  r = ((r << 1) ^ p->poly);
	else
	  r <<= 1;

      r = (p->rout) ? rbit(r, p->len) : r;

      crc_table[i] = (r & m);
    }
}

u64 crc(const ascii *in, u64 len, crc_param_t *p)
{
  u64 m = ~0;
  u64 crc = 0;

  if (p->len < 64)
    m = (1ULL << p->len) - 1;

  build_crc_table(p, m);

  crc = (p->rin) ? rbit(p->iv, p->len) : p->iv;

  for (u64 i = 0; i < len; i++)
    {
      if (p->rout)
	crc = (crc >> 8) ^ crc_table[(crc & 0xFF) ^ in[i]];
      else
	crc = (crc << 8) ^ crc_table[(crc >> (p->len - 8)) ^ in[i]];
      
      crc &= m;
    }
  
  return (crc ^ p->xor) & m;
}
