#include <string>
#include "filesystem.h"
#include "file.h"
#include "directory.h"
#include "iterator.h"

virt::fs::iterator::iterator(virt::filesystem& fs, virt::fs::directory* dir):
	working_fs(fs), working_dir(dir){}

bool virt::fs::iterator::move_to(
