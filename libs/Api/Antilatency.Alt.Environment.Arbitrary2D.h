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
#include <Antilatency.InterfaceContract.h>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4946)
#pragma warning(disable: 4265)
#endif
namespace Antilatency {
	namespace Alt {
		namespace Environment {
			namespace Arbitrary2D {
				/* copy and paste this to implementer
				std::vector<Antilatency::Math::float2> getMarkers() {
					throw std::logic_error{"Method IDeserializedEnvironment.getMarkers() is not implemented."};
				}
				float getHeight() {
					throw std::logic_error{"Method IDeserializedEnvironment.getHeight() is not implemented."};
				}
				Antilatency::InterfaceContract::LongBool getFloor() {
					throw std::logic_error{"Method IDeserializedEnvironment.getFloor() is not implemented."};
				}
				*/
				struct IDeserializedEnvironment : Antilatency::InterfaceContract::IInterface {
					struct VMT : Antilatency::InterfaceContract::IInterface::VMT {
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getMarkers(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getHeight(float& result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getFloor(Antilatency::InterfaceContract::LongBool& result) = 0;
						static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
							return Antilatency::InterfaceContract::InterfaceID{0x7dbbed9f,0x593b,0x426e,{0xa9,0xff,0xcb,0x87,0x69,0x29,0x39,0x40}};
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
					std::vector<Antilatency::Math::float2> getMarkers() {
						std::vector<Antilatency::Math::float2> result;
						auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getMarkers(resultMarshaler));
						return result;
					}
					float getHeight() {
						float result;
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getHeight(result));
						return result;
					}
					Antilatency::InterfaceContract::LongBool getFloor() {
						Antilatency::InterfaceContract::LongBool result;
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->getFloor(result));
						return result;
					}
				};
			} //namespace Arbitrary2D
		} //namespace Environment
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::InterfaceContract::IInterface, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getMarkers(Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					try {
						result = this->_object->getMarkers();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getHeight(float& result) {
					try {
						result = this->_object->getHeight();
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL getFloor(Antilatency::InterfaceContract::LongBool& result) {
					try {
						result = this->_object->getFloor();
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
			namespace Arbitrary2D {
				/* copy and paste this to implementer
				std::string serialize(const std::vector<Antilatency::Math::float2>& markers, float height, Antilatency::InterfaceContract::LongBool floor) {
					throw std::logic_error{"Method ILibrary.serialize() is not implemented."};
				}
				Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment deserialize(const std::string& environmentData) {
					throw std::logic_error{"Method ILibrary.deserialize() is not implemented."};
				}
				*/
				struct ILibrary : Antilatency::Alt::Environment::IEnvironmentConstructor {
					struct VMT : Antilatency::Alt::Environment::IEnvironmentConstructor::VMT {
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL serialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate markers, float height, Antilatency::InterfaceContract::LongBool floor, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) = 0;
						virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL deserialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate environmentData, Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment& result) = 0;
						static constexpr Antilatency::InterfaceContract::InterfaceID ID() {
							return Antilatency::InterfaceContract::InterfaceID{0xc2df5d47,0x1d06,0x4467,{0x93,0xdc,0x46,0xcc,0xb7,0xcb,0xc3,0x20}};
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
					std::string serialize(const std::vector<Antilatency::Math::float2>& markers, float height, Antilatency::InterfaceContract::LongBool floor) {
						std::string result;
						auto markersMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(markers);
						auto resultMarshaler = Antilatency::InterfaceContract::Details::ArrayOutMarshaler::create(result);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->serialize(markersMarshaler, height, floor, resultMarshaler));
						return result;
					}
					Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment deserialize(const std::string& environmentData) {
						Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment result;
						auto environmentDataMarshaler = Antilatency::InterfaceContract::Details::ArrayInMarshaler::create(environmentData);
						handleExceptionCode((reinterpret_cast<VMT*>(this->_object))->deserialize(environmentDataMarshaler, result));
						return result;
					}
				};
			} //namespace Arbitrary2D
		} //namespace Environment
	} //namespace Alt
} //namespace Antilatency
namespace Antilatency {
	namespace InterfaceContract {
		namespace Details {
			template<typename Implementer, typename LifeTimeController>
			struct InterfaceRemap<Antilatency::Alt::Environment::Arbitrary2D::ILibrary, Implementer, LifeTimeController> : Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::Alt::Environment::IEnvironmentConstructor, Implementer, LifeTimeController> {
			public:
			    InterfaceRemap() = default;
			    static bool isInterfaceSupported(const Antilatency::InterfaceContract::InterfaceID& id) {
					if (id == Antilatency::Alt::Environment::Arbitrary2D::ILibrary::VMT::ID()) {
						return true;
					}
					return Antilatency::InterfaceContract::Details::InterfaceRemap<Antilatency::Alt::Environment::IEnvironmentConstructor, Implementer, LifeTimeController>::isInterfaceSupported(id);
				}
			public:
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL serialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate markers, float height, Antilatency::InterfaceContract::LongBool floor, Antilatency::InterfaceContract::Details::ArrayOutMarshaler::Intermediate result) {
					try {
						result = this->_object->serialize(markers, height, floor);
					}
					catch (...) {
						return Antilatency::InterfaceContract::handleRemapException(this->_object);
					}
					return Antilatency::InterfaceContract::ExceptionCode::Ok;
				}
				virtual Antilatency::InterfaceContract::ExceptionCode ANTILATENCY_INTERFACE_CALL deserialize(Antilatency::InterfaceContract::Details::ArrayInMarshaler::Intermediate environmentData, Antilatency::Alt::Environment::Arbitrary2D::IDeserializedEnvironment& result) {
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
