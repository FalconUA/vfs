#ifndef __VIRTUAL_UTILITY_TOUCH_HEADER__
#define __VIRTUAL_UTILITY_TOUCH_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class touch: public virt::os::utility {
	public:
		touch(virt::operatingsystem* os):
				utility(os) {
			description = "Создаёт файл с заданным текстом и названием в текущей папке. Для детальной информации пропишите 'help touch'.\n";

			help_text = description + "Синтаксис: touch [filename] [content], где [filename] (пишите без квадратных скобочек) - это название файла которую хотите создать (обязательный параметр). Название не должно содержать символы '/' или ' ', и не должен совпадать с резервированными названиями '', '.', '..'. [content] - необязательный параметр, который задаёт текст файла.\n";
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
			std::string filename = param.substr(0, p);

			if (filename.find(' ') != std::string::npos || filename.find('/') != std::string::npos
					|| filename == "" || filename == "." || filename == "..")
				return "Invalid file name. Please see 'help touch' for more information.\n";

			param.erase(0, p+1);

			sh->shell_iterator.get_working_dir()->add_file(filename, param, false);
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
