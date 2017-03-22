#pragma once

//p1 判定したい1つ目のオブジェクトの座標
//p2 判定したい2つ目のオブジェクトの座標
//r1 判定したい1つ目のオブジェクトの半径
//r2 判定したい2つ目のオブジェクトの半径
//BallCollision(PlayerPos,EnemyPos,PlayerRadius,EnemyRadius);
bool BallCollision(const D3DXVECTOR3& p1,const D3DXVECTOR3& p2,float r1,float r2);
