OBJS=lagrange.o
CFLAGS=`root-config --cflags`
GLIBS=`root-config --glibs`

Lagrange: $(OBJS)
	g++ -o lagrange $(OBJS) $(CFLAGS) $(GLIBS) 

lagrange.o: lagrange.C
	g++ -c lagrange.C $(CFLAGS) 

clean:
	rm -f *.o
