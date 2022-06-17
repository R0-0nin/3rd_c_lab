#include <stdio.h> 
#include <string.h>
#include <crtdbg.h>
#include <corecrt_malloc.h>
#pragma warning(disable : 4996)

typedef struct
{
	char FN[128];
	char LN[128];
	char Gndr[128];
	char Occ[128];
	int  Slr;
} employee;
void v(char s[], int* k, char field[])
{

	int i = *k;
	while ((s[i] == ',') || (s[i] == '\"'))
	{
		i++;
	}
	int j = 0;
	while (s[i] != '\"')
	{
		field[j] = s[i];
		i++;
		j++;
	}
	field[j] = '\0';
	*k = i;
}
int main(int argc, char* argv[])
{
	FILE* f;
	char s[255];

	int N = 0, i;
	
	employee* m = NULL;
	employee tmp;
	int dl;

	if (argc == 3)
	{
		sscanf_s(argv[2], "%d", &dl);
		if ((dl > 0) && (dl < 11))
		{
			if (!(fopen_s(&f, argv[1], "r")))
			{
				fgets(s, 255, f);
				while (!feof(f))
				{
					fgets(s, 255, f);
					m = (employee*)realloc(m, (N + 1) * sizeof(employee));
					i = 0;
					v(s, &i, m[N].FN);
					v(s, &i, m[N].LN);
					v(s, &i, m[N].Gndr);
					v(s, &i, m[N].Occ);
					sscanf_s(&s[i + 3], "%d", &m[N].Slr);
					N++;
				}
				fclose(f);
		
				for (i = 0; i < N - 1; i++)
				{
					for (int j = 0; j < N - 1 - i; j++)
					{
						if (m[j].Slr > m[j + 1].Slr)
						{
							
							memcpy(&tmp, &m[j], sizeof(employee));
							memcpy(&m[j], &m[j + 1], sizeof(employee));
							memcpy(&m[j + 1], &tmp, sizeof(employee));
						}
					}
				}
							
				int Zp = 0;
				for (i = (dl - 1) * N / 10; i < dl * N / 10; i++)
				{
					Zp += m[i].Slr;
				}
				
				printf("Decile %d Sum salary %d\n", dl, Zp);



			}
			else
				printf("file not found\n");
		}
		else
			printf("uncorrect decile\n");
	}
	else
		printf("parameters error\n");
	return 0;
}
