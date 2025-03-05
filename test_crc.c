#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "crc.h"

crc_param_t test_vector[] = {
  
  //CRC-16
  { "CRC-16/CCITT-0"   ,  0x1021, 0xFFFF, 0, 0, 0x0   , 0x29B1, 16 },
  { "CRC-16/ARC"       ,  0x8005, 0x0   , 1, 1, 0x0   , 0xBB3D, 16 },
  { "CRC-16/AUG-CCITT" ,  0x1021, 0x1D0F, 0, 0, 0x0   , 0xE5CC, 16 },
  { "CRC-16/BUYPASS"   ,  0x8005, 0x0   , 0, 0, 0x0   , 0xFEE8, 16 },
  { "CRC-16/CDMA2000"  ,  0xC867, 0xFFFF, 0, 0, 0x0   , 0x4C06, 16 },
  { "CRC-16/DDS-110"   ,  0x8005, 0x800D, 0, 0, 0x0   , 0x9ECF, 16 },
  { "CRC-16/DECT-R"    ,  0x589 , 0x0   , 0, 0, 0x1   , 0x007E, 16 },
  { "CRC-16/DECT-X"    ,  0x589 , 0x0   , 0, 0, 0x0   , 0x007F, 16 },
  { "CRC-16/DNP"       ,  0x3D65, 0x0   , 1, 1, 0xFFFF, 0xEA82, 16 },
  { "CRC-16/EN-13757"  ,  0x3D65, 0x0   , 0, 0, 0xFFFF, 0xC2B7, 16 },
  { "CRC-16/GENIBUS"   ,  0x1021, 0xFFFF, 0, 0, 0xFFFF, 0xD64E, 16 },
  { "CRC-16/KERMIT"    ,  0x1021, 0x0   , 1, 1, 0x0   , 0x2189, 16 },
  { "CRC-16/MAXIM"     ,  0x8005, 0x0   , 1, 1, 0xFFFF, 0x44C2, 16 },
  { "CRC-16/MCRF4XX"   ,  0x1021, 0xFFFF, 1, 1, 0x0   , 0x6F91, 16 },
  { "CRC-16/MODBUS"    ,  0x8005, 0xFFFF, 1, 1, 0x0   , 0x4B37, 16 },
  { "CRC-16/RIELLO"    ,  0x1021, 0xB2AA, 1, 1, 0x0   , 0x63D0, 16 },
  { "CRC-16/T10-DIF"   ,  0x8BB7, 0x0   , 0, 0, 0x0   , 0xD0DB, 16 },
  { "CRC-16/TELEDISK"  ,  0xA097, 0x0   , 0, 0, 0x0   , 0x0FB3, 16 },
  { "CRC-16/TMS37157"  ,  0x1021, 0x89EC, 1, 1, 0x0   , 0x26B1, 16 },
  { "CRC-16/USB"       ,  0x8005, 0xFFFF, 1, 1, 0xFFFF, 0xB4C8, 16 },
  { "CRC-16/X-25"      ,  0x1021, 0xFFFF, 1, 1, 0xFFFF, 0x906E, 16 },
  { "CRC-16/XMODEM"    ,  0x1021, 0x0   , 0, 0, 0x0   , 0x31C3, 16 },
  { "CRC-A"            ,  0x1021, 0xc6c6, 1, 1, 0x0   , 0xBF05, 16 },
  
  //CRC-32
  { "CRC-32"           ,  0x04C11DB7, 0xFFFFFFFF, 1, 1, 0xFFFFFFFF, 0xCBF43926, 32 },
  { "CRC-32/BZIP2"     ,  0x04C11DB7, 0xFFFFFFFF, 0, 0, 0xFFFFFFFF, 0xFC891918, 32 },
  { "CRC-32/JAMCRC"    ,  0x04C11DB7, 0xFFFFFFFF, 1, 1, 0x00000000, 0x340BC6D9, 32 },
  { "CRC-32/MPEG-2"    ,  0x04C11DB7, 0xFFFFFFFF, 0, 0, 0x00000000, 0x0376E6E7, 32 },
  { "CRC-32/POSIX"     ,  0x04C11DB7, 0x00000000, 0, 0, 0xFFFFFFFF, 0x765E7680, 32 },
  { "CRC-32/XFER"      ,  0x000000AF, 0x00000000, 0, 0, 0x00000000, 0xBD0BE338, 32 },
  { "CRC-32C"          ,  0x1EDC6F41, 0xFFFFFFFF, 1, 1, 0xFFFFFFFF, 0xE3069283, 32 },
  { "CRC-32D"          ,  0xA833982B, 0xFFFFFFFF, 1, 1, 0xFFFFFFFF, 0x87315576, 32 },
  { "CRC-32Q"          ,  0x814141AB, 0x00000000, 0, 0, 0x00000000, 0x3010BF7F, 32 },

  //CRC-64
  { "CRC-64"           , 0x42F0E1EBA9EA3693L, 0x00000000L        , 0, 0, 0x00000000L        , 0x6C40DF5F0B497347L, 64 },
  { "CRC-64/WE"        , 0x42F0E1EBA9EA3693L, 0xFFFFFFFFFFFFFFFFL, 0, 0, 0xFFFFFFFFFFFFFFFFL, 0x62EC59E3F1A4F00AL, 64 },
  { "CRC-64/XZ"        , 0x42F0E1EBA9EA3693L, 0xFFFFFFFFFFFFFFFFL, 1, 1, 0xFFFFFFFFFFFFFFFFL, 0x995DC9BBDF1939FAL, 64 },
};

int main(void)
{
  const ascii in[] = "123456789";
  u64 len = strlen(in);

  u64 hash = 0;
  u64 fails = 0;
  
  //CRC-16
  printf("CRC-16\n");
  for (u64 i = 0; i < 23; i++)
    {
      hash = crc(in, len, &test_vector[i]);
      
      printf("%s; %llu; TV: 0x%04llx; HASH: 0x%04llx\n", in, len, test_vector[i].tv, hash);
      
      if (hash != test_vector[i].tv)
	fails++;
    }

  printf("CRC-16 fails: %llu\n\n", fails);

  fails = 0;
  
  //CRC-32
  printf("CRC-32\n");
  for (u64 i = 23; i < 32; i++)
    {
      hash = crc(in, len, &test_vector[i]);
      
      printf("%s; %llu; TV: 0x%08llx; HASH: 0x%08llx\n", in, len, test_vector[i].tv, hash);
      
      if (hash != test_vector[i].tv)
	fails++;
    }
  
  printf("CRC-32 fails: %llu\n\n", fails);
  
  fails = 0;
    
  //CRC-64
  printf("CRC-64\n");
  for (u64 i = 32; i < 35; i++)
    {
      hash = crc(in, len, &test_vector[i]);
      
      printf("%s; %llu; TV: 0x%016llx; HASH: 0x%016llx\n", in, len, test_vector[i].tv, hash);
      
      if (hash != test_vector[i].tv)
	fails++;
    }
  
  printf("CRC-64 fails: %llu\n", fails);
  
  return 0;
}
