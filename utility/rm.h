#ifndef __VIRTUAL_UTILITY_RM_HEADER__
#define __VIRTUAL_UTILITY_RM_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class rm: public virt::os::utility {
	public:
		rm(virt::operatingsystem* os):
				utility(os) {
			description = "Удаляет папку или файл, если такой существует. Для большей информации пропишите в консоле 'help rm'";

			help_text = description + "\nСинтаксис: rm [unitname]\nГде вместо [unitname] вставляете имя папки или файла которую хотите удалить. Помните: в названиях не должно присутствовать символы ' ' (пробел) или '/' (слэш)!\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!\n";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			sh->shell_iterator.get_working_dir()->remove_file(param);
			sh->shell_iterator.get_working_dir()->remove_subdir(param);
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
