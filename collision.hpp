#pragma once


template<class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
  return  mA.right() >= mB.left() && mA.left() <= mB.right()
       && mA.top() <= mB.bottom() && mA.bottom() >= mB.top();
}

void testCollision(Paddle& mPaddle, Ball& mBall)
{
  // if no collision get out from the function
  if(!isIntersecting(mPaddle, mBall)) return;

  mBall.velocity.y = -ballVelocity;

  // direct ball depends where's paddle was hit
  if(mBall.x() < mPaddle.x())
    mBall.velocity.x = -ballVelocity;
  else
    mBall.velocity.x = ballVelocity;
}

void testCollision(Brick& mBrick, Ball& mBall)
{
  if(!isIntersecting(mBrick, mBall)) return;

  mBrick.destroyed = true;

  float overlapLeft{mBall.right() - mBrick.left()};
  float overlapRight{mBrick.right() - mBall.left()};
  float overlapTop{mBall.bottom() - mBall.top()};
  float overlapBottom{mBrick.bottom() - mBall.top()};

  bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
  bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

  float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
  float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

  // upon assumptions
  if(abs(minOverlapX) < abs(minOverlapY))
    mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
  else
    mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}
