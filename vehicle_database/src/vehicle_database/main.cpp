
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#include "vehicle_database/tokens/common_property_token.h"
#include "vehicle_database/enums/vehicle_type_enum.h"
#include <print>
#include <span>

namespace apperoso {

	void runDemo()
	{
		std::println("Key=[{}] Property=[{}]", make.keyName(), make.propertyName());
		std::println("Key=[{}] Property=[{}]", model.keyName(), model.propertyName());
		std::println("Key=[{}] Property=[{}]", color.keyName(), color.propertyName());
		std::println("sizeof(make) = [{}]", sizeof(make));
	}

}

int main() {

	std::println("Welcome to the Vehicle Database demo!");

	apperoso::runDemo();
}
