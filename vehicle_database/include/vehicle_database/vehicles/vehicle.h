
///////////////////////////////////////////////////////////////////////////
// 
// Copyright(c) 2024, Apperoso Ltd
// All rights reserved.
//
// This source code is licensed under the BSD - style license found in the
// LICENSE file in the root directory of this source tree.
// 
///////////////////////////////////////////////////////////////////////////

#pragma once

#include "vehicle_database/vehicles/vehicle_definitions.h"
#include <string>
#include <memory>

namespace apperoso {

	class Vehicle {
		struct Concept {
			virtual ~Concept() = default;
			virtual PropertyStatus setProperty(VehiclePropertyToken propertyToken, std::string_view value) = 0;
			virtual PropertyResult getProperty(VehiclePropertyToken propertyToken) const = 0;
			virtual std::unique_ptr<Concept> clone() const = 0;
		};

		template<typename VehicleT>
		struct Model : public Concept {
			Model(VehicleT vehicle) : vehicle_{ std::move(vehicle) } {}

			std::unique_ptr<Concept> clone() const override {
				return std::make_unique<Model>(*this);
			}

			PropertyStatus setProperty(VehiclePropertyToken propertyToken, std::string_view value) override {
				return vehicle_.setProperty(propertyToken, value);
			}

			PropertyResult getProperty(VehiclePropertyToken propertyToken) const override {
				return vehicle_.getProperty(propertyToken);
			}

			VehicleT vehicle_;
		};

		std::unique_ptr<Concept> vehiclePtr_;

	public:
		template<typename VehicleT>
		Vehicle(VehicleT vehicle) : vehiclePtr_{ std::make_unique<Model<VehicleT>>(std::move(vehicle)) } {}

		Vehicle(Vehicle const& vehicle) : vehiclePtr_{ vehicle.vehiclePtr_->clone() } {}

		PropertyStatus setProperty(VehiclePropertyToken propertyToken, std::string_view value) {
			return vehiclePtr_->setProperty(propertyToken, value);
		}

		PropertyResult getProperty(VehiclePropertyToken propertyToken) const {
			return vehiclePtr_->getProperty(propertyToken);
		}
	};

}