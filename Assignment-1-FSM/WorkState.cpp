//#include "WorkState.h"

//WorkState::WorkState(AgentState state) : State2(){}
//{
//	
//}

//void WorkState::enter(Agent* e)
//{
//}
//
//void WorkState::execute(Agent* e)
//{
//	double time = Timer::instance().getTime();
//	
//	if (e->getWorkTimer() <= time)
//	{
//		std::cout << Timer::instance().getTimeString() << e->getName() << ": " << e->getWork().getActiveJobExecuteLine() << std::endl;
//		e->setWorkTimer(time + e->getWorkCD());
//		e->increaseFatigue(e->getWork().getJobIntensity());
//		std::cout << e->getFatigue() << std::endl;
//	}
//}
//
//void WorkState::exit(Agent* e)
//{
//}
