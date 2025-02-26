#ifndef CHECKPOINT_H
#define CHECKPOINT_H

struct Checkpoint {
  int x;
  int y;
  int penalty;

  Checkpoint (int xx = 0, int yy = 0, int p = 0)
  : x(xx), y(yy), penalty(p)
  {
  }


};

#endif
