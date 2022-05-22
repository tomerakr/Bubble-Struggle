
using foo =  int(*)(int);

int func(int x)
{
	return x;
}

int func2(int y)
{
	return y;
}

int main()
{
	foo a = func;

	a = func2;
	a(3);
}