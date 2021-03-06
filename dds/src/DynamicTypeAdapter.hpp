/*
 * Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef SOSS__DDS__DYNAMICTYPEADAPTER_HPP
#define SOSS__DDS__DYNAMICTYPEADAPTER_HPP

#include <fastrtps/types/DynamicData.h>
#include <fastrtps/types/DynamicDataPtr.h>
#include <fastrtps/types/DynamicDataFactory.h>
#include <fastrtps/types/DynamicTypeBuilder.h>
#include <fastrtps/types/DynamicTypeBuilderPtr.h>
#include <fastrtps/types/DynamicTypeBuilderFactory.h>
#include <fastrtps/types/DynamicTypeMember.h>
#include <fastrtps/types/DynamicPubSubType.h>
#include <fastrtps/types/MemberDescriptor.h>
#include <fastrtps/types/TypesBase.h>
#include <fastrtps/attributes/PublisherAttributes.h>

namespace soss {
namespace dds {

using DynamicData_ptr = eprosima::fastrtps::types::DynamicData_ptr;

#if 1 < FASTRTPS_VERSION_MAJOR || (1 == FASTRTPS_VERSION_MAJOR && 8 <= FASTRTPS_VERSION_MINOR)

using eprosima::fastrtps::rtps::NO_KEY;
using eprosima::fastrtps::rtps::ALIVE;

using DynamicTypeBuilder = eprosima::fastrtps::types::DynamicTypeBuilder;
using DynamicDataFactory = eprosima::fastrtps::types::DynamicDataFactory;
using DynamicTypeBuilderFactory = eprosima::fastrtps::types::DynamicTypeBuilderFactory;

using DynamicData = eprosima::fastrtps::types::DynamicData;

// Due to a problem with Fast-RTPS library, which by now does not export the "GetDescriptor" function for windows,
// this workaround is needed in order to access the protected member "mDescriptors".
// This problem will be solved in future fixes, but for now this workaround is the only way of introspecting
// dynamic types in windows.
class DynamicDataSOSS : public soss::dds::DynamicData
{
public:

    eprosima::fastrtps::types::ResponseCode GetDescriptorSOSS(
            eprosima::fastrtps::types::MemberDescriptor& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        auto it = descriptors_.find(id);
        if (it != descriptors_.end())
        {
            return value.copy_from(it->second);
        }
        else
        {
            std::cerr << "Error getting MemberDescriptor. MemberId not found." << std::endl;
            return eprosima::fastrtps::types::ResponseCode::RETCODE_BAD_PARAMETER;
        }
    }

};

using MemberDescriptor = eprosima::fastrtps::types::MemberDescriptor;

#else

using eprosima::fastrtps::NO_KEY;
using eprosima::fastrtps::ALIVE;

using octet = eprosima::fastrtps::octet;

class DynamicData : public eprosima::fastrtps::types::DynamicData
{
public:

    DynamicData()
        : eprosima::fastrtps::types::DynamicData()
    {
    }

    DynamicData(
            const eprosima::fastrtps::types::DynamicData& dyn_data)
        : eprosima::fastrtps::types::DynamicData(dyn_data)
    {
    }

    DynamicData(
            eprosima::fastrtps::types::DynamicData&& dyn_data)
        : eprosima::fastrtps::types::DynamicData(std::move(dyn_data))
    {
    }

    DynamicData& operator = (
            const eprosima::fastrtps::types::DynamicData& other)
    {
        eprosima::fastrtps::types::DynamicData::operator =(
                other);
        return *this;
    }

    DynamicData& operator = (
            eprosima::fastrtps::types::DynamicData&& other)
    {
        eprosima::fastrtps::types::DynamicData::operator =(
                std::move(other));
        return *this;
    }

    eprosima::fastrtps::types::ResponseCode get_descriptor(
            eprosima::fastrtps::types::MemberDescriptor& value,
            eprosima::fastrtps::types::MemberId id)
    {
        return eprosima::fastrtps::types::DynamicData::GetDescriptor(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_descriptor(
            eprosima::fastrtps::types::MemberId id,
            const eprosima::fastrtps::types::MemberDescriptor* value)
    {
        return eprosima::fastrtps::types::DynamicData::SetDescriptor(id, value);
    }

    eprosima::fastrtps::types::ResponseCode clear_all_values()
    {
        return eprosima::fastrtps::types::DynamicData::ClearAllValues();
    }

    eprosima::fastrtps::types::ResponseCode clear_nonkey_values()
    {
        return eprosima::fastrtps::types::DynamicData::ClearNonkeyValues();
    }

    eprosima::fastrtps::types::ResponseCode clear_value(
            eprosima::fastrtps::types::MemberId id)
    {
        return eprosima::fastrtps::types::DynamicData::ClearValue(id);
    }

    bool equals(
            const DynamicData* other) const
    {
        return eprosima::fastrtps::types::DynamicData::Equals(other);
    }

    uint32_t get_item_count() const
    {
        return eprosima::fastrtps::types::DynamicData::GetItemCount();
    }

    std::string get_name()
    {
        return eprosima::fastrtps::types::DynamicData::GetName();
    }

    eprosima::fastrtps::types::MemberId get_member_id_by_name(
            const std::string& name) const
    {
        return eprosima::fastrtps::types::DynamicData::GetMemberIdByName(name);
    }

    eprosima::fastrtps::types::MemberId get_member_id_at_index(
            uint32_t index) const
    {
        return eprosima::fastrtps::types::DynamicData::GetMemberIdAtIndex(index);
    }

    DynamicData* loan_value(
            eprosima::fastrtps::types::MemberId id)
    {
        return static_cast<DynamicData*>(eprosima::fastrtps::types::DynamicData::LoanValue(id));
    }

    eprosima::fastrtps::types::ResponseCode return_loaned_value(
            const DynamicData* value)
    {
        return eprosima::fastrtps::types::DynamicData::ReturnLoanedValue(value);
    }

    eprosima::fastrtps::types::MemberId get_array_index(
            const std::vector<uint32_t>& position)
    {
        return eprosima::fastrtps::types::DynamicData::GetArrayIndex(position);
    }

    eprosima::fastrtps::types::ResponseCode insert_sequence_data(
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertSequenceData(outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_int32_value(
            int32_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertInt32Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_uint32_value(
            uint32_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertUint32Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_int16_value(
            int16_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertInt16Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_uint16_value(
            uint16_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertUint16Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_int64_value(
            int64_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertInt64Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_uint64_value(
            uint64_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertUint64Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_float32_value(
            float value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertFloat32Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_float64_value(
            double value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertFloat64Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_float128_value(
            long double value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertFloat128Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_char8_value(
            char value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertChar8Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_char16_value(
            wchar_t value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertChar16Value(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_byte_value(
            octet value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertByteValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_bool_value(
            bool value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertBoolValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_string_value(
            const std::string& value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertStringValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_wstring_value(
            const std::wstring& value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertWstringValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_enum_value(
            const std::string& value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertEnumValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_complex_value(
            const DynamicData* value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertComplexValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_complex_value(
            DynamicData* value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertComplexValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode insert_complex_value(
            eprosima::fastrtps::types::DynamicData_ptr value,
            eprosima::fastrtps::types::MemberId& outId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertComplexValue(value, outId);
    }

    eprosima::fastrtps::types::ResponseCode remove_sequence_data(
            eprosima::fastrtps::types::MemberId id)
    {
        return eprosima::fastrtps::types::DynamicData::RemoveSequenceData(id);
    }

    eprosima::fastrtps::types::ResponseCode clear_data()
    {
        return eprosima::fastrtps::types::DynamicData::ClearData();
    }

    eprosima::fastrtps::types::ResponseCode clear_array_data(
            eprosima::fastrtps::types::MemberId indexId)
    {
        return eprosima::fastrtps::types::DynamicData::ClearArrayData(indexId);
    }

    eprosima::fastrtps::types::ResponseCode insert_map_data(
            const DynamicData* key,
            eprosima::fastrtps::types::MemberId& outKeyId,
            eprosima::fastrtps::types::MemberId& outValueId)
    {
        return eprosima::fastrtps::types::DynamicData::InsertMapData(key, outKeyId, outValueId);
    }

    eprosima::fastrtps::types::ResponseCode insert_map_data(
            const DynamicData* key,
            DynamicData* value,
            eprosima::fastrtps::types::MemberId& outKey,
            eprosima::fastrtps::types::MemberId& outValue)
    {
        return eprosima::fastrtps::types::DynamicData::InsertMapData(key, value, outKey, outValue);
    }

    eprosima::fastrtps::types::ResponseCode insert_map_data(
            const DynamicData* key,
            const DynamicData* value,
            eprosima::fastrtps::types::MemberId& outKey,
            eprosima::fastrtps::types::MemberId& outValue)
    {
        return eprosima::fastrtps::types::DynamicData::InsertMapData(key, value, outKey, outValue);
    }

    eprosima::fastrtps::types::ResponseCode insert_map_data(
            const DynamicData* key,
            eprosima::fastrtps::types::DynamicData_ptr value,
            eprosima::fastrtps::types::MemberId& outKey,
            eprosima::fastrtps::types::MemberId& outValue)
    {
        return eprosima::fastrtps::types::DynamicData::InsertMapData(key, value, outKey, outValue);
    }

    eprosima::fastrtps::types::ResponseCode remove_map_data(
            eprosima::fastrtps::types::MemberId keyId)
    {
        return eprosima::fastrtps::types::DynamicData::RemoveMapData(keyId);
    }

    eprosima::fastrtps::types::ResponseCode get_int32_value(
            int32_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_int32_value(
            int32_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetInt32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_uint32_value(
            uint32_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_uint32_value(
            uint32_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetUint32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_int16_value(
            int16_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_int16_value(
            int16_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetInt16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_uint16_value(
            uint16_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_uint16_value(
            uint16_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetUint16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_int64_value(
            int64_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_int64_value(
            int64_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetInt64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_uint64_value(
            uint64_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_uint64_value(
            uint64_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetUint64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_float32_value(
            float& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_float32_value(
            float value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetFloat32Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_float64_value(
            double& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_float64_value(
            double value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetFloat64Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_float128_value(
            long double& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat128Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_float128_value(
            long double value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetFloat128Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_char8_value(
            char& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetChar8Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_char8_value(
            char value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetChar8Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_char16_value(
            wchar_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetChar16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_char16_value(
            wchar_t value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetChar16Value(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_byte_value(
            octet& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetByteValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_byte_value(
            octet value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetByteValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_bool_value(
            bool& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetBoolValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_bool_value(
            bool value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetBoolValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_string_value(
            std::string& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetStringValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_string_value(
            const std::string& value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetStringValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_wstring_value(
            std::wstring& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetWstringValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_wstring_value(
            const std::wstring& value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetWstringValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_enum_value(
            std::string& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetEnumValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_enum_value(
            const std::string& value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetEnumValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_enum_value(
            uint32_t& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetEnumValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode set_enum_value(
            const uint32_t& value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetEnumValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_bitmask_value(
            const std::string& name,
            bool& value) const
    {
        return eprosima::fastrtps::types::DynamicData::GetBitmaskValue(name, value);
    }

    eprosima::fastrtps::types::ResponseCode set_bitmask_value(
            bool value,
            const std::string& name)
    {
        return eprosima::fastrtps::types::DynamicData::SetBitmaskValue(value, name);
    }

    eprosima::fastrtps::types::ResponseCode get_complex_value(
            DynamicData** value,
            eprosima::fastrtps::types::MemberId id) const
    {
        eprosima::fastrtps::types::DynamicData* temp = *value;
        eprosima::fastrtps::types::ResponseCode result =
                eprosima::fastrtps::types::DynamicData::GetComplexValue(&temp, id);
        //*value = static_cast<DynamicData*>(temp);
        return result;

    }

    eprosima::fastrtps::types::ResponseCode set_complex_value(
            DynamicData* value,
            eprosima::fastrtps::types::MemberId id = MEMBER_ID_INVALID)
    {
        return eprosima::fastrtps::types::DynamicData::SetComplexValue(value, id);
    }

    eprosima::fastrtps::types::ResponseCode get_union_label(
            uint64_t& value) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUnionLabel(value);
    }

    // Basic types returns (copy)
    int32_t get_int32_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt32Value(id);
    }

    uint32_t get_uint32_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint32Value(id);
    }

    int16_t get_int16_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt16Value(id);
    }

    uint16_t get_uint16_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint16Value(id);
    }

    int64_t get_int64_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetInt64Value(id);
    }

    uint64_t get_uint64_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetUint64Value(id);
    }

    float get_float32_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat32Value(id);
    }

    double get_float64_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat64Value(id);
    }

    long double get_float128_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetFloat128Value(id);
    }

    char get_char8_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetChar8Value(id);
    }

    wchar_t get_char16_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetChar16Value(id);
    }

    octet get_byte_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetByteValue(id);
    }

    bool get_bool_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetBoolValue(id);
    }

    std::string get_string_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetStringValue(id);
    }

    std::wstring get_wstring_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetWstringValue(id);
    }

    std::string get_enum_value(
            eprosima::fastrtps::types::MemberId id) const
    {
        return eprosima::fastrtps::types::DynamicData::GetEnumValue(id);
    }

    bool get_bitmask_value(
            const std::string& name) const
    {
        return eprosima::fastrtps::types::DynamicData::GetBitmaskValue(name);
    }

    uint64_t get_union_label() const
    {
        return eprosima::fastrtps::types::DynamicData::GetUnionLabel();
    }

};

// Due to a problem with Fast-RTPS library, which by now does not export the "GetDescriptor" function for windows,
// this workaround is needed in order to access the protected member "mDescriptors".
// This problem will be solved in future fixes, but for now this workaround is the only way of introspecting
// dynamic types in windows.
class DynamicDataSOSS : public soss::dds::DynamicData
{
public:

    eprosima::fastrtps::types::ResponseCode GetDescriptorSOSS(
            eprosima::fastrtps::types::MemberDescriptor& value,
            eprosima::fastrtps::types::MemberId id) const
    {
        auto it = mDescriptors.find(id);
        if (it != mDescriptors.end())
        {
            return value.CopyFrom(it->second);
        }
        else
        {
            std::cerr << "Error getting MemberDescriptor. MemberId not found." << std::endl;
            return eprosima::fastrtps::types::ResponseCode::RETCODE_BAD_PARAMETER;
        }
    }

};

class MemberDescriptor : public eprosima::fastrtps::types::MemberDescriptor
{
public:

    MemberDescriptor()
        : eprosima::fastrtps::types::MemberDescriptor ()
    {
    }

    MemberDescriptor(
            uint32_t index,
            const std::string& name)
        : eprosima::fastrtps::types::MemberDescriptor (index, name)
    {
    }

    MemberDescriptor(
            eprosima::fastrtps::types::MemberId id,
            const std::string& name,
            eprosima::fastrtps::types::DynamicType_ptr mType)
        : eprosima::fastrtps::types::MemberDescriptor (id, name, mType)
    {
    }

    MemberDescriptor(
            eprosima::fastrtps::types::MemberId id,
            const std::string& name,
            eprosima::fastrtps::types::DynamicType_ptr mType,
            const std::string& defaultValue)
        : eprosima::fastrtps::types::MemberDescriptor (id, name, mType, defaultValue)
    {
    }

    MemberDescriptor(
            eprosima::fastrtps::types::MemberId id,
            const std::string& name,
            eprosima::fastrtps::types::DynamicType_ptr mType,
            const std::string& defaultValue,
            const std::vector<uint64_t>& unionLabels,
            bool isDefaultLabel)
        : eprosima::fastrtps::types::MemberDescriptor (id, name, mType, defaultValue, unionLabels, isDefaultLabel)
    {
    }

    MemberDescriptor(
            const MemberDescriptor* descriptor)
        : eprosima::fastrtps::types::MemberDescriptor (descriptor)
    {
    }

    bool check_union_labels(
            const std::vector<uint64_t>& labels) const
    {
        return eprosima::fastrtps::types::MemberDescriptor::CheckUnionLabels(labels);
    }

    eprosima::fastrtps::types::ResponseCode copy_from(
            const MemberDescriptor* other)
    {
        return eprosima::fastrtps::types::MemberDescriptor::CopyFrom(other);
    }

    bool equals(
            const MemberDescriptor* other) const
    {
        return eprosima::fastrtps::types::MemberDescriptor::Equals(other);
    }

    eprosima::fastrtps::types::TypeKind get_kind() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::GetKind();
    }

    eprosima::fastrtps::types::MemberId get_id() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::GetId();
    }

    uint32_t get_index() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::GetIndex();
    }

    std::string get_name() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::GetName();
    }

    std::vector<uint64_t> get_union_labels() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::GetUnionLabels();
    }

    bool is_default_union_value() const
    {
        return eprosima::fastrtps::types::MemberDescriptor::IsDefaultUnionValue();
    }

    bool is_consistent(
            eprosima::fastrtps::types::TypeKind parentKind) const
    {
        return eprosima::fastrtps::types::MemberDescriptor::IsConsistent(parentKind);
    }

    void add_union_case_index(
            uint64_t value)
    {
        return eprosima::fastrtps::types::MemberDescriptor::AddUnionCaseIndex(value);
    }

    void set_id(
            eprosima::fastrtps::types::MemberId id)
    {
        return eprosima::fastrtps::types::MemberDescriptor::SetId(id);
    }

    void set_index(
            uint32_t index)
    {
        return eprosima::fastrtps::types::MemberDescriptor::SetIndex(index);
    }

    void set_name(
            const std::string& name)
    {
        return eprosima::fastrtps::types::MemberDescriptor::SetName(name);
    }

    void set_type(
            eprosima::fastrtps::types::DynamicType_ptr type)
    {
        return eprosima::fastrtps::types::MemberDescriptor::SetType(type);
    }

    void set_default_union_value(
            bool bDefault)
    {
        return eprosima::fastrtps::types::MemberDescriptor::SetDefaultUnionValue(bDefault);
    }

};

class DynamicTypeBuilder : public eprosima::fastrtps::types::DynamicTypeBuilder
{
public:
    eprosima::fastrtps::types::DynamicType_ptr build()
    {
        return eprosima::fastrtps::types::DynamicTypeBuilder::Build();
    }

    eprosima::fastrtps::types::ResponseCode set_name(
            const std::string& name)
    {
        return eprosima::fastrtps::types::DynamicTypeBuilder::SetName(name);
    }

    eprosima::fastrtps::types::ResponseCode add_empty_member(
            uint32_t index,
            const std::string& name)
    {
        return eprosima::fastrtps::types::DynamicTypeBuilder::AddEmptyMember(index, name);
    }

    eprosima::fastrtps::types::ResponseCode add_member(
            eprosima::fastrtps::types::MemberId id,
            const std::string& name,
            DynamicTypeBuilder* mType = nullptr)
    {
        return eprosima::fastrtps::types::DynamicTypeBuilder::AddMember(id, name, mType);
    }
};

class DynamicDataFactory : public eprosima::fastrtps::types::DynamicDataFactory
{
public:
    static DynamicDataFactory* get_instance()
    {
        return static_cast<DynamicDataFactory*>(eprosima::fastrtps::types::DynamicDataFactory::GetInstance());
    }

    DynamicData* create_data(
            eprosima::fastrtps::types::DynamicType_ptr pType)
    {
        return static_cast<DynamicData*>(eprosima::fastrtps::types::DynamicDataFactory::CreateData(pType));
    }
};

class DynamicTypeBuilderFactory : public eprosima::fastrtps::types::DynamicTypeBuilderFactory
{
public:
    static DynamicTypeBuilderFactory* get_instance()
    {
        return static_cast<DynamicTypeBuilderFactory*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::GetInstance());
    }

    eprosima::fastrtps::types::ResponseCode delete_builder(
            DynamicTypeBuilder* builder)
    {
        return eprosima::fastrtps::types::DynamicTypeBuilderFactory::DeleteBuilder(builder);
    }

    DynamicTypeBuilder* create_int32_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateInt32Builder());
    }

    DynamicTypeBuilder* create_uint32_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateUint32Builder());
    }

    DynamicTypeBuilder* create_int16_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateInt16Builder());
    }

    DynamicTypeBuilder* create_uint16_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateUint16Builder());
    }

    DynamicTypeBuilder* create_int64_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateInt64Builder());
    }

    DynamicTypeBuilder* create_uint64_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateUint64Builder());
    }

    DynamicTypeBuilder* create_float32_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateFloat32Builder());
    }

    DynamicTypeBuilder* create_float64_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateFloat64Builder());
    }

    DynamicTypeBuilder* create_float128_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateFloat128Builder());
    }

    DynamicTypeBuilder* create_char8_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateChar8Builder());
    }

    DynamicTypeBuilder* create_char16_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateChar16Builder());
    }

    DynamicTypeBuilder* create_bool_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateBoolBuilder());
    }

    DynamicTypeBuilder* create_byte_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateByteBuilder());
    }

    DynamicTypeBuilder* create_array_builder(
            const DynamicTypeBuilder* element_type,
            const std::vector<uint32_t>& bounds)
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateArrayBuilder(element_type, bounds));
    }

    DynamicTypeBuilder* create_enum_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateEnumBuilder());
    }

    DynamicTypeBuilder* create_struct_builder()
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateStructBuilder());
    }

    DynamicTypeBuilder* create_string_builder(
            uint32_t bound = eprosima::fastrtps::types::MAX_STRING_LENGTH)
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateStringBuilder(bound));
    }

    DynamicTypeBuilder* create_wstring_builder(
            uint32_t bound = eprosima::fastrtps::types::MAX_STRING_LENGTH)
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateWstringBuilder(bound));
    }

    DynamicTypeBuilder* create_alias_builder(
            DynamicTypeBuilder* base_type,
            const std::string& sName)
    {
        return static_cast<DynamicTypeBuilder*>(
            eprosima::fastrtps::types::DynamicTypeBuilderFactory::CreateAliasBuilder(base_type, sName));
    }
};

#endif // Fast version >= 1.8.0

} // dds
} // soss

#endif // SOSS__DDS__DYNAMICTYPEADAPTER_HPP
