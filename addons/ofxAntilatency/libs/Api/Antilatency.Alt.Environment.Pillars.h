//Copyright 2021, ALT LLC. All Rights Reserved.
//This file is part of Antilatency SDK.
//It is subject to the license terms in the LICENSE file found in the top-level directory
//of this distribution and at http://www.antilatency.com/eula
//You may not use this file except in compliance with the License.
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
#pragma once
#ifndef ANTILATENCY_INTERFACE_CONTRACT_EXCEPTIONS_ENABLED
#define ANTILATENCY_INTERFACE_CONTRACT_EXCEPTIONS_ENABLED
#endif
#include <Antilatency.Alt.Environment.h>
#include <Antilatency.Math.h>
#include <cstdint>
#include <Antilatency.InterfaceContract.h>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4946)
#pragma warning(disable: 4265)
#endif
namespace Antilatency {
	namespace Alt {
		namespace Environment {
			namespace Pillars {
				struct PillarData {
					Antilatency::Math::float3 position;
					uint32_t kind;
				};
			} //namespace Pillars
		} //namespace Environment
	} //namespace Alt
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Environment {
			namespace Pillars {
				/* copy and paste this to implementer
				std::vector<Antilatency::Alt::Environment::Pillars::PillarData> getPillars() {
					throw std::logic_error{"Method IDeserializedEnvironment.getPillars() is not implemented."};
				}
				std::vector<float> getProportions() {
					throw std::logic_error{"Method IDeserializedEnvironment.getProportions() is not implemented."};
				}
				uint32_t getNumMarkersPerPillar() {
					throw std::logic_error{"Method IDeserializedEnvironment.getNumMarkersPerPillar() is not implemented."};
				}
				float getPillarLength() {
					throw std::logic_error{"Method IDeserializedEnvironment.getPillarLength() is not implemented."};
				}
				*/
				struct IDeserializedEnvironment : Antilatency::InterfaceContract::IInterface {
					struct VMT : Antilatency::InterfaceContract::IInterface::VMT {
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getPillars(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getProportions(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getNumMarkersPerPillar(uint32_t& result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getPillarLength(float& result) = 0;
						static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
							return Antilatency::InterfaceContract::InterfaceID{0x50d5c3b4,0x88a5,0x4dec,{0x9d,0x20,0x2d,0x0d,0x8f,0x65,0x05,0xbc}};
						}
					private:
						~VMT() = delete;
					};
					IDeserializedEnvironment() = default;
					IDeserializedEnvironment(std::nullptr_t) {}
					explicit IDeserializedEnvironment(VMT* pointer) : Antilatency::InterfaceContract::IInterface(pointer) {}
					template<typename T, typename = typename std::enable_if<std::is_base_of<IDeserializedEnvironment, T>::value>::type>
					IDeserializedEnvironment& operator = (const T& other) {
					    Antilatency::InterfaceContract::IInterface::operator=(other);
					    return *this;
					}
					template<class Implementer, class ... TArgs>
					static IDeserializedEnvironment create(TArgs&&... args) {
					    return *new Implementer(std::forward<TArgs>(args)...);
					}
					void attach(VMT* other) ANTILATENCY_NOEXCEPT {
					    Antilatency::InterfaceContract::IInterface::attach(other);
					}
					VMT* detach() ANTILATENCY_NOEXCEPT {
					    return reinterpret_cast<VMT*>(Antilatency::InterfaceContract::IInterface::detach());
					}
					std::vector<Antilatency::Alt::Environment::Pillars::PillarData> getPillars() {
						std::vector<Antilatency::Alt::Environment::Pillars::PillarData> result;
						auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getPillars(resultMarshaler));
						return result;
					}
					std::vector<float> getProportions() {
						std::vector<float> result;
						auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getProportions(resultMarshaler));
						return result;
					}
					uint32_t getNumMarkersPerPillar() {
						uint32_t result;
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getNumMarkersPerPillar(result));
						return result;
					}
					float getPillarLength() {
						float result;
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getPillarLength(result));
						return result;
					}
				};
			} //namespace Pillars
		} //namespace Environment
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getPillars(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					try {
						result = this->_object->getPillars();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getProportions(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					try {
						result = this->_object->getProportions();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getNumMarkersPerPillar(uint32_t& result) {
					try {
						result = this->_object->getNumMarkersPerPillar();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getPillarLength(float& result) {
					try {
						result = this->_object->getPillarLength();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency

namespace Antilatency {
	namespace Alt {
		namespace Environment {
			namespace Pillars {
				/* copy and paste this to implementer
				std::string serialize(const std::vector<Antilatency::Alt::Environment::Pillars::PillarData>& pillars, const std::vector<float>& proportions, uint32_t numMarkersPerPillar, float pillarLength) {
					throw std::logic_error{"Method ILibrary.serialize() is not implemented."};
				}
				Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment deserialize(const std::string& environmentData) {
					throw std::logic_error{"Method ILibrary.deserialize() is not implemented."};
				}
				*/
				struct ILibrary : Antilatency::Alt::Environment::IEnvironmentConstructor {
					struct VMT : Antilatency::Alt::Environment::IEnvironmentConstructor::VMT {
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL serialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate pillars, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate proportions, uint32_t numMarkersPerPillar, float pillarLength, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL deserialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate environmentData, Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment& result) = 0;
						static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
							return Antilatency::InterfaceContract::InterfaceID{0xfb691fa6,0xccd5,0x4b82,{0xaa,0xd9,0x13,0xd7,0x0a,0x8b,0x83,0x22}};
						}
					private:
						~VMT() = delete;
					};
					ILibrary() = default;
					ILibrary(std::nullptr_t) {}
					explicit ILibrary(VMT* pointer) : Antilatency::Alt::Environment::IEnvironmentConstructor(pointer) {}
					template<typename T, typename = typename std::enable_if<std::is_base_of<ILibrary, T>::value>::type>
					ILibrary& operator = (const T& other) {
					    Antilatency::Alt::Environment::IEnvironmentConstructor::operator=(other);
					    return *this;
					}
					template<class Implementer, class ... TArgs>
					static ILibrary create(TArgs&&... args) {
					    return *new Implementer(std::forward<TArgs>(args)...);
					}
					void attach(VMT* other) ANTILATENCY_NOEXCEPT {
					    Antilatency::Alt::Environment::IEnvironmentConstructor::attach(other);
					}
					VMT* detach() ANTILATENCY_NOEXCEPT {
					    return reinterpret_cast<VMT*>(Antilatency::Alt::Environment::IEnvironmentConstructor::detach());
					}
					std::string serialize(const std::vector<Antilatency::Alt::Environment::Pillars::PillarData>& pillars, const std::vector<float>& proportions, uint32_t numMarkersPerPillar, float pillarLength) {
						std::string result;
						auto pillarsMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(pillars);
						auto proportionsMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(proportions);
						auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->serialize(pillarsMarshaler, proportionsMarshaler, numMarkersPerPillar, pillarLength, resultMarshaler));
						return result;
					}
					Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment deserialize(const std::string& environmentData) {
						Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment result;
						auto environmentDataMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(environmentData);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->deserialize(environmentDataMarshaler, result));
						return result;
					}
				};
			} //namespace Pillars
		} //namespace Environment
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Environment::Pillars::ILibrary, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::Alt::Environment::IEnvironmentConstructor, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Environment::Pillars::ILibrary::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::Alt::Environment::IEnvironmentConstructor, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL serialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate pillars, Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate proportions, uint32_t numMarkersPerPillar, float pillarLength, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					try {
						result = this->_object->serialize(pillars, proportions, numMarkersPerPillar, pillarLength);
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL deserialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate environmentData, Antilatency::Alt::Environment::Pillars::IDeserializedEnvironment& result) {
					try {
						result = this->_object->deserialize(environmentData);
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
			};
		} //namespace Details
	} //namespace InterfaceContract
} //namespace Antilatency


#ifdef _MSC_VER
#pragma warning(pop)
#endif
