compile()
{
	for file in ./*.cpp
	do
			g++ -c $file -o $(echo $file | sed -e 's/cpp/o/g');	
	done
}

link()
{
	g++ *.o -o main;
}

clean()
{
	rm *.o;
}

execute()
{
	if [ "$1" = "build" ]; then
		compile;
		link;
	elif [ "$1" = "clean" ]; then
		clean;
	else
		compile;
		link;
	fi
}

execute;
