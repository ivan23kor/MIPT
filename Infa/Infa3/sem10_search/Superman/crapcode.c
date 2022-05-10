/*if (i == 0)
	{
		if (j == 0)
		{
			printf("1)i = %d, j = %d\n", i, j);
			MY_IF (i_right, j_right)
			//if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);
		}
		else if (j == length - 1)
		{
			printf("2)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
		}
		else
		{
			printf("3)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
			if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);
		}
		if ((strings[i_down][j_down] != '#') && (strings[i_down][j_down] != 'S'))
				stack_push (stack_1, position + length);
	}
	else if (i == strings_count - 1)
	{
		if ((strings[i_up][j_up] != '#') && (strings[i_up][j_up] != 'S'))
				stack_push (stack_1, position - length);
		if (j == 0)
		{
			printf("4)i = %d, j = %d\n", i, j);
			if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);
		}
		else if (j == length - 1)
		{
			printf("5)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
		}
		else
		{
			printf("6)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
			if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);
		}
	}
	else
	{
		if ((strings[i_up][j_up] != '#') && (strings[i_up][j_up] != 'S'))
			stack_push (stack_1, position - length);
		if (j == 0)
		{
			printf("7)i = %d, j = %d\n", i, j);
			if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);	
		}
		else if (j == length - 1)
		{
			printf("8)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
		}
		else
		{
			printf("9)i = %d, j = %d\n", i, j);
			if ((strings[i_left][j_left] != '#') && (strings[i_left][j_left] != 'S'))
				stack_push (stack_1, position - 1);
			if ((strings[i_right][j_right] != '#') && (strings[i_right][j_right] != 'S'))
				stack_push (stack_1, position + 1);
		}
		if ((strings[i_down][j_down] != '#') && (strings[i_down][j_down] != 'S'))
			stack_push (stack_1, position + length);
	}*/
