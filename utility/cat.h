#ifndef __VIRTUAL_UTILITY_CAT_HEADER__
#define __VIRTUAL_UTILITY_CAT_HEADER__

#include <string>
#include <map>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class cat: public virt::os::utility {
	public:
		cat(virt::operatingsystem* os):
				utility(os) {
			description = "Показывает текст в файле. Для подробной инструкции пропишите 'help cat'.\n";
			help_text = description + "Синтаксис: cat [filename], где [filename] - названия файла в текущей папке. Помните: в названиях не должно присутствовать символы '/' и ' ' (слэш и пробел)\n";

		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!\n";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			if (param.find('/') != std::string::npos || param.find(' ') != std::string::npos)
				return "invalid characters '/' or ' ' in filename. See 'help cat' for more information.\n";

			std::map<std::string, virt::fs::file*>::iterator it = sh->shell_iterator.get_working_dir()->files.find(param);
			if (it == sh->shell_iterator.get_working_dir()->files.end())
				return "ERROR: No such file in current directory. For more help see 'help cat'.\n";
			return sh->shell_iterator.get_working_dir()->files[param]->content + "\n";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
