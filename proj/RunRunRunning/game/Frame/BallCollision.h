#pragma once

//p1 ���肵����1�ڂ̃I�u�W�F�N�g�̍��W
//p2 ���肵����2�ڂ̃I�u�W�F�N�g�̍��W
//r1 ���肵����1�ڂ̃I�u�W�F�N�g�̔��a
//r2 ���肵����2�ڂ̃I�u�W�F�N�g�̔��a
//BallCollision(PlayerPos,EnemyPos,PlayerRadius,EnemyRadius);
bool BallCollision(const D3DXVECTOR3& p1,const D3DXVECTOR3& p2,float r1,float r2);
