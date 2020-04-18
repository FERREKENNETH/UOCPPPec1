#include "music.h"

/**************************************************************************/
  int main (void)
/**************************************************************************/
{
  tMusicStore ms;

  /* section a */
  init_music_store (&ms);

  /* section b */
  new_instrument (&ms, 107, "Electric Guitar Gibson SG Tribute Walnut", 875.0);
  new_instrument (&ms, 351, "Drums Set Tama Imperialstar IE52KH6W Black", 671.43);
  new_instrument (&ms, 437, "Digital Piano Roland FP-30 with Black Stand", 719.99);
  new_instrument (&ms, 405, "Violin acoustic Primavera 200 Natural Walnut", 116.80);
  new_instrument (&ms, 351, "Microphone Shure SM 58 LCE dynamic Silver", 83.20);
  new_instrument (&ms, 229, "Saxophone Yamaha YAS-280 Eb-Alto Gold Lacquer", 834.08);

  /* section c */
  add_stock (&ms, 351, 3);
  add_stock (&ms, 405, 1);
  add_stock (&ms, 229, 3);
  add_stock (&ms, 100, 10);
  add_stock (&ms, 351, 7);
  add_stock (&ms, 437, 20);
  add_stock (&ms, 405, 7);

  /* section d*/
  print_stock (ms);

  return 0;
}

