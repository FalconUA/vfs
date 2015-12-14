#ifndef __VIRTUAL_UTILITY_CD_HEADER__
#define __VIRTUAL_UTILITY_CD_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class cd: public virt::os::utility {
	public:
		cd(virt::operatingsystem* os):
				utility(os) {
			description = "Перемещается в указанном в параметре папку. Для более детальной информации пропишите 'help cd'.\n";
			help_text = description + "Синтаксис: cd [path], где [path] (пишите без квадратных скобочек) это путь к папке в которую хотите переместиться. ВАЖНО: если [path] начинается с символа '/', то это означает что мы будем перемещаться от корня файловой системы, иначе будем перемещаться от текущей папки.\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!\n";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			bool s = sh->shell_iterator.move_to(param);
			if (!s)
				return "No such directory. See 'help cd' for more information";
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
