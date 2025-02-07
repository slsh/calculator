// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "../Common/Utils.h"

namespace CalculatorApp::ViewModel
{
public
    ref class GridDisplayItems sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        GridDisplayItems();

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Expression);
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Direction);
    };

public
    ref class KeyGraphFeaturesItem sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        KeyGraphFeaturesItem();

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_RW(Platform::String ^, Title);
        OBSERVABLE_PROPERTY_RW(Windows::Foundation::Collections::IObservableVector<Platform::String ^> ^, DisplayItems);
        OBSERVABLE_PROPERTY_RW(Windows::Foundation::Collections::IObservableVector<GridDisplayItems ^> ^, GridItems);
        OBSERVABLE_PROPERTY_RW(bool, IsText);
    };


public
    ref class EquationViewModel sealed : public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        EquationViewModel(GraphControl::Equation ^ equation);

        OBSERVABLE_OBJECT();
        OBSERVABLE_PROPERTY_R(GraphControl::Equation ^, GraphEquation);
        OBSERVABLE_PROPERTY_RW(int, FunctionLabelIndex);
        OBSERVABLE_PROPERTY_RW(bool, IsLastItemInList);

        property Platform::String ^ Expression
        {
            Platform::String ^ get()
            {
                return GraphEquation->Expression;
            }
            void set(Platform::String ^ value)
            {
                if (GraphEquation->Expression != value)
                {
                    GraphEquation->Expression = value;
                    RaisePropertyChanged("Expression");
                }
            }
        }

        property Windows::UI::Xaml::Media::SolidColorBrush ^ LineColor
        {
            Windows::UI::Xaml::Media::SolidColorBrush ^ get()
            {
                return GraphEquation->LineColor;
            }
            void set(Windows::UI::Xaml::Media::SolidColorBrush ^ value)
            {
                if (GraphEquation->LineColor != value)
                {
                    GraphEquation->LineColor = value;
                    RaisePropertyChanged("LineColor");
                }
            }
        }

        property bool IsLineEnabled
        {
            bool get()
            {
                return GraphEquation->IsLineEnabled;
            }
            void set(bool value)
            {
                if (GraphEquation->IsLineEnabled != value)
                {
                    GraphEquation->IsLineEnabled = value;
                    RaisePropertyChanged("IsLineEnabled");
                }
            }
        }

        // Key Graph Features
        OBSERVABLE_PROPERTY_R(Platform::String ^, AnalysisErrorString);
        OBSERVABLE_PROPERTY_R(bool, AnalysisErrorVisible);
        OBSERVABLE_PROPERTY_R(Windows::Foundation::Collections::IObservableVector<CalculatorApp::ViewModel::KeyGraphFeaturesItem ^> ^, KeyGraphFeaturesItems)

        void PopulateKeyGraphFeatures();

    private:
        void AddKeyGraphFeature(Platform::String ^ title, Platform::String ^ expression, Platform::String ^ errorString);
        void AddKeyGraphFeature(
            Platform::String ^ title,
            Windows::Foundation::Collections::IVector<Platform::String ^> ^ expressionVector,
            Platform::String ^ errorString);
        void AddParityKeyGraphFeature();
        void AddPeriodicityKeyGraphFeature();
        void AddMonotoncityKeyGraphFeature();
        void AddTooComplexKeyGraphFeature();

        Windows::Foundation::Collections::IObservableMap<Platform::String ^, Platform::String ^> ^ m_Monotonicity;
        Windows::ApplicationModel::Resources::ResourceLoader ^ m_resourceLoader;
    };

}
