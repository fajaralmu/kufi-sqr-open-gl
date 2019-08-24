#pragma once
#include "BaseEntity.h"
namespace Entity {
	class AppObject : public BaseEntity
	{
	public:
		AppObject(std::string vp, std::string tp)
		{
			this->vertPath = vp;
			this->texPath = tp;
			init();
		}
		~AppObject();
		void init();
		
	};
}

