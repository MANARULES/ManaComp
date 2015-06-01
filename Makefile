OBJS=lagrange.o
CFLAGS=`root-config --cflags`
GLIBS=`root-config --glibs`

Lagrange: $(OBJS)
	g++ -o lagrange $(OBJS) $(CFLAGS) $(GLIBS) 

lagrange.o: lagrange.C
	g++ -c lagrange.C $(CFLAGS) 

Lagrange5: lagrange5.o
	g++ -o lagrange5 lagrange5.o $(CFLAGS) $(GLIBS) 

lagrange5.o: lagrange5.C
	g++ -c lagrange5.C $(CFLAGS) 

clean:
	rm -f *.o
