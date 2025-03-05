#pragma once

#include "types.h"

typedef struct crc_param_s {

  //Description
  ascii *str;

  //Polynomial
  u64 poly;

  //Initial value
  u64 iv;

  //Reverse bits of input
  i8 rin;
  
  //Reverse bits of output
  i8 rout;

  //XOR final value
  u64 xor;

  //Test vector
  u64 tv;

  //Length of CRC in bits
  u64 len; 
  
} crc_param_t;

u64 crc(const ascii *in, u64 len, crc_param_t *p);
