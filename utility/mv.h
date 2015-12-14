#ifndef __VIRTUAL_UTILITY_MV_HEADER__
#define __VIRTUAL_UTILITY_MV_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class mv: public virt::os::utility {
	public:
		mv(virt::operatingsystem* os):
				utility(os) {
			description = "Переносит целиком заданную папку в другую директорию. Для более детальной информации пропишите 'help mv'.\n";

			help_text = description + "Синтаксис: mv [source_path] [destination_path], где [source_path] это папка которого будем перемещать, а [destination_path] - папка, куда будем перемещать [source_path]. ВАЖНО: папки '', '.', '..' перемещать нельзя\n";
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
				return "Invalid second file name. Please see 'help mv' for more information.\n";
			param.erase(0, p+1);

			virt::filesystem::dir_iterator it_dest(sh->shell_iterator);
			it_dest.move_to(param);

			bool b = virt::fs::move_subdir(first_path, sh->shell_iterator.get_working_dir(), it_dest.get_working_dir());
			if (!b)
				return "Cannot move this directory. See 'help mv' for more information.\n";
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
