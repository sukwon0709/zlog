/*
 * This file is part of the Xlog Library.
 *
 * Copyright (C) 2011 by Hardy Simpson <HardySimpson@gmail.com>
 *
 * The Xlog Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Xlog Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the Xlog Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static FILE *fp;

int work(long loop_count)
{
	while(loop_count-- > 0) {
		fprintf(fp, "2011-10-24 17:00:14 | 14644:test.c:11 | 日志日志\n");
	}
	return 0;
}


int test(long process_count, long loop_count)
{
	long i;
	pid_t pid;

	for (i = 0; i < process_count; i++) {
		pid = fork();
		if (pid < 0) {
			printf("fork fail\n");
		} else if(pid == 0) {
			work(loop_count);
			return 0;
		}
	}

	for (i = 0; i < process_count; i++) {
		pid = wait(NULL);
	}

	return 0;
}


int main(int argc, char** argv)
{
	FILE *fp;

	if (argc != 3) {
		fprintf(stderr, "test nprocess nloop\n");
		exit(1);
	}

	fp = fopen("press.log", "a");
	if (!fp) {
		printf("fopen fail\n");
		return 1;
	}

	test(atol(argv[1]), atol(argv[2]));

	fclose(fp);
	
	return 0;
}