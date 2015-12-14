#ifndef __VIRTUAL_UTILITY_CP_HEADER__
#define __VIRTUAL_UTILITY_CP_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class cp: public virt::os::utility {
	public:
		cp(virt::operatingsystem* os):
				utility(os) {
			description = "Копирует целиком все файлы заданной директории в другую папку. Для более детальной информации пропишите 'help cp'.\n";

			help_text = description + "Синтаксис: cp [source_path] [destination_path], где [source_path] это папка из которого будем копировать, а [destination_path] - папка, куда будем копировать папки и файлы из [source_path]. ВАЖНО: папки '', '.', '..' перемещать нельзя\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			std::size_t p = std::min(param.find(' '), param.length());	
			std::string first_path = param.substr(0, p);

			if (first_path.find(' ') != std::string::npos || first_path.find('/') != std::string::npos
					|| first_path == "" || first_path == "." || first_path == "..")
				return "Invalid second file name. Please see 'help cp' for more information.\n";
			param.erase(0, p+1);

			virt::filesystem::dir_iterator it_source = sh->shell_iterator;
			virt::filesystem::dir_iterator it_dest = sh->shell_iterator;

			if (it_dest.get_working_dir()->path().find(it_source.get_working_dir()->path()))
				return "Cannot copy: destination is a sub directory of source. See 'help cp'\n";

			bool b = true;

			b = b && it_source.move_to(first_path);
			b = b && it_dest.move_to(param);

			if (!b)
				return "Directory not found. See 'help mv' for more information.\n";
			
			virt::fs::copy_content(it_source.get_working_dir(), it_dest.get_working_dir());
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
