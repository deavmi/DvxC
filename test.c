int main()
{
	struct f
	{
		char a;		
		char b;
		int k;
	};

	struct f g;
	struct f d;

	g.a = 2;
	d.b = g.a;
	d.b++;
}