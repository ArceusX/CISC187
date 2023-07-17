#include "change.h"

purchase_t buy_stuff () {
  purchase_t purchase;


  /*But due to the fact that floating - point numbers cannot be represented exactly,
    but rather as the closest sum of powers of 2, floating - point numbers can be
    stored inaccurately.Thus, any math that is done with floating point numbers
    must account for some epsilon margin of error.
    i.e. 0.1 is actually store as 0.1000000000000000055511151231257827021181583404541015625
  */
  for (int price = 10; purchase.funds >= price; price += 10) {
    purchase.funds -= price;
    purchase.items += 1;
  }

  return purchase;
}



