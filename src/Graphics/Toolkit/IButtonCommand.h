#ifndef IBUTTONCOMMAND_H_
#define IBUTTONCOMMAND_H_

namespace InGE{

class IButtonCommand
{
	public:
		IButtonCommand() {}
		virtual ~IButtonCommand() {}
		
		virtual void onClicked() = 0;
};

};
#endif /*IBUTTONCOMMAND_H_*/
