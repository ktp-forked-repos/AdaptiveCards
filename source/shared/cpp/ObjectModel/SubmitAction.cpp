// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "ParseUtil.h"
#include "SubmitAction.h"

using namespace AdaptiveSharedNamespace;

SubmitAction::SubmitAction() : BaseActionElement(ActionType::Submit)
{
    PopulateKnownPropertiesSet();
}

std::string SubmitAction::GetDataJson() const
{
    return ParseUtil::JsonToString(m_dataJson);
}

Json::Value SubmitAction::GetDataJsonAsValue() const
{
    return m_dataJson;
}

void SubmitAction::SetDataJson(const std::string value)
{
    SetDataJson(ParseUtil::GetJsonValueFromString(value));
}

void SubmitAction::SetDataJson(const Json::Value& value)
{
    m_dataJson = value;
}

Json::Value SubmitAction::SerializeToJsonValue() const
{
    Json::Value root = BaseActionElement::SerializeToJsonValue();

    if (!m_dataJson.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)] = m_dataJson;
    }

    return root;
}

std::shared_ptr<BaseActionElement> SubmitActionParser::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<SubmitAction> submitAction = BaseActionElement::Deserialize<SubmitAction>(context, json);

    submitAction->SetDataJson(ParseUtil::ExtractJsonValue(json, AdaptiveCardSchemaKey::Data));

    return submitAction;
}

std::shared_ptr<BaseActionElement> SubmitActionParser::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return SubmitActionParser::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

void SubmitAction::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Data)});
}
