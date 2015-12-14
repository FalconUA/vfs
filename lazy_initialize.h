#ifndef __LAZYINIT_HEADER__
#define __LAZYINIT_HEADER__

#include <string>

#include "virtualfs.h"
#include "virtualos.h"
#include "utility/shell.h"

#include "utility/ls.h"
#include "utility/cd.h"
#include "utility/pwd.h"
#include "utility/mkdir.h"
#include "utility/cat.h"
#include "utility/help.h"
#include "utility/touch.h"
#include "utility/rm.h"

// we are too lazy to implement the import from physical file and export to physical file
// for our virtual file system, so we will create a sample hierarchy manually :)
void sample_filesystem(virt::operatingsystem& os){
	os.launch_utility("mkdir", "a");
	os.launch_utility("mkdir", "b");
	os.launch_utility("mkdir", "c");
	os.launch_utility("mkdir", "d");

	os.launch_utility("touch", "1.txt Заметки на сегодня: \n1. покормить кота\n2. покормить жену\n3. покормить детей\n");
	os.launch_utility("touch", "2.txt Заметки на завтра: \n1. купить кот\n2. найти жену\n3. создать детей\n");

	os.launch_utility("cd", "a");
	os.launch_utility("mkdir", "e");
	os.launch_utility("mkdir", "f");
	os.launch_utility("mkdir", "g");
	
	os.launch_utility("touch", "txt Этот файл лежит в папке а. Прикольно :)");
	os.launch_utility("cd", "e");

	os.launch_utility("mkdir", "ololo");
	os.launch_utility("cd", "ololo");
	os.launch_utility("mkdir", "trololo");

	os.launch_utility("cd", "/");
}



#endif
