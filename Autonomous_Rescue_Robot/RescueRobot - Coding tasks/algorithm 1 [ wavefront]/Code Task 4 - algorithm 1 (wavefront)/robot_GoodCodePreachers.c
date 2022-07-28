
#include "robot_GoodCodePreachers.h"
#include <stdio.h>

char pre;
int pu;
int Tposition;

int z = -1;
int move(char* world, int map_id)
{
	int going[200];
	int returning[200];

	if (z != map_id)
	{
		z = map_id;
		pu = 1;
		pre = 'O';
	}



	if (pu == 1) {

		for (int i = 0; i < 200; i++)
		{
			if (world[i] == 'T' || world[i] == 't') { Tposition = i; }
		}
		pu = pu + 1;
	}

	if (world[Tposition] == 'T' || world[Tposition] == 't')
	{
		int robot;
		for (int i = 0; i < 200; ++i) {
			if (world[i] == 'R') {
				robot = i;
			}
		}


		int a, n, e, w, s;
		goingArray1(going, world);


		a = going[robot];

		n = robot - 21;
		e = robot + 1;
		w = robot - 1;
		s = robot + 21;

		if (going[n] == (a - 1))
		{
			if ((world[n] == '~' && pre == 'O') || (world[n] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}

			else if (world[n] == '*') { return 6; }

			else { return 1; }
		}
		else if (going[e] == (a - 1))
		{
			if ((world[e] == '~' && pre == 'O') || (world[e] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[e] == '*') { return 7; }
			else { return 2; }
		}
		else if (going[w] == (a - 1))
		{
			if ((world[w] == '~' && pre == 'O') || (world[w] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[w] == '*') { return 9; }
			else { return 4; }
		}
		else if (going[s] == (a - 1))
		{
			if ((world[s] == '~' && pre == 'O') || (world[s] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[s] == '*') { return 8; }
			else { return 3; }
		}
	}

	else
	{

		int robot;
		int aa, nn, ee, ww, ss;
		returning1(returning, world);

		for (int i = 0; i < 200; ++i) {
			if (world[i] == 'R') {
				robot = i;
			}
		}


		aa = returning[robot];

		nn = robot - 21;
		ee = robot + 1;
		ww = robot - 1;
		ss = robot + 21;

		if (returning[nn] == (aa - 1))
		{
			if ((world[nn] == '~' && pre == 'O') || (world[nn] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[nn] == '*') { return 6; }
			else { return 1; }
		}
		else if (returning[ee] == (aa - 1))
		{
			if ((world[ee] == '~' && pre == 'O') || (world[ee] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[ee] == '*') { return 7; }
			else { return 2; }
		}
		else if (returning[ww] == (aa - 1))
		{
			if ((world[ww] == '~' && pre == 'O') || (world[ww] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[ww] == '*') { return 9; }
			else { return 4; }
		}
		else if (returning[ss] == (aa - 1))
		{
			if ((world[ss] == '~' && pre == 'O') || (world[ss] == 'O' && pre == '~'))
			{
				if (pre == 'O') { pre = '~'; }
				else { pre = 'O'; }
				return 5;
			}
			else if (world[ss] == '*') { return 8; }
			else { return 3; }
		}
	}


}
int goingArray1(int* going, char* world)
{

	for (int i = 0; i<200; i++)
	{
		if (world[i] == '#')
		{
			going[i] = -1;
		}
		else if (world[i] == 'T' || world[i] == 't')
		{
			going[i] = 1;
		}
		else if (world[i] == '*')
		{
			going[i] = 0;
		}
		else if (world[i] == 'X')
		{
			going[i] = 0;
		}
		else if (world[i] == 'R')
		{
			going[i] = 0;
		}
		else if (world[i] == 'O')
		{
			going[i] = 0;
		}
		else if (world[i] == '~')
		{
			going[i] = 0;
		}

		else { going[i] = 0; }

	}


	goingArray2(going, world, 1);
}
int goingArray2(int* going, char*world, int z)
{
	int n, e, w, s, p, j;

	for (int i = 0; i<200; i++)
	{


		if (going[i] == z)
		{
			p = i;
			n = p - 21;
			e = p + 1;
			w = p - 1;
			s = p + 21;

			if (going[n] != -1 && going[n] == 0)
			{
				going[n] = z + 1;
			}

			if (going[e] != -1 && going[e] == 0)
			{
				going[e] = z + 1;
			}
			if (going[w] != -1 && going[w] == 0)
			{
				going[w] = z + 1;
			}
			if (going[s] != -1 && going[s] == 0)
			{
				going[s] = z + 1;
			}
		}
	}

	for (int k = 0; k<200; k++) { if (world[k] == 'R') { j = k; } }
	if (going[j] == 0) { goingArray2(going, world, z + 1); }
}


int returning1(int* returning, char* world)
{

	for (int i = 0; i<200; i++)
	{
		if (world[i] == '#')
		{
			returning[i] = -1;
		}
		else if (world[i] == 'T' || world[i] == 't')
		{
			returning[i] = 0;
		}
		else if (world[i] == '*')
		{
			returning[i] = 0;
		}
		else if (world[i] == 'X')
		{
			returning[i] = 1;
		}

		else if (world[i] == 'O')
		{
			returning[i] = 0;
		}
		else if (world[i] == '~')
		{
			returning[i] = 0;
		}

		else { returning[i] = 0; }

	}


	returning2(returning, world, 1);
}
int returning2(int* returning, char*world, int zz)
{
	int nn, ee, ww, ss, pp, jj;

	for (int i = 0; i<200; i++)
	{


		if (returning[i] == zz)
		{
			pp = i;
			nn = pp - 21;
			ee = pp + 1;
			ww = pp - 1;
			ss = pp + 21;

			if (returning[nn] != -1 && returning[nn] == 0)
			{
				returning[nn] = zz + 1;
			}

			if (returning[ee] != -1 && returning[ee] == 0)
			{
				returning[ee] = zz + 1;
			}
			if (returning[ww] != -1 && returning[ww] == 0)
			{
				returning[ww] = zz + 1;
			}
			if (returning[ss] != -1 && returning[ss] == 0)
			{
				returning[ss] = zz + 1;
			}
		}
	}

	for (int ii = 0; ii<200; ii++) { if (world[ii] == 'R') { jj = ii; } }
	if (returning[jj] == 0) { returning2(returning, world, zz + 1); }




}
