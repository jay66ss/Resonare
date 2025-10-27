/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class ResonareAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ResonareAudioProcessor();
    ~ResonareAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    juce::dsp::Gain<float> gain;
    float pi = juce::MathConstants<float>::pi;
    
    //juce::dsp::Oscillator<float> osc {[] (float x) {return std::sin(x); }}; // Sine wave
    juce::dsp::Oscillator<float> osc {
        [] (float x) {
            constexpr float pi = juce::MathConstants<float>::pi;
            return std::tanh(5*pi*std::sin(x)) * (4*x / (x < 0 ? -pi : pi) + pi*x);
        }
    };

    //juce::dsp::Oscillator<float> osc {[] (float x) {return x<0.0f ? -1.0f : 1.0f; }}; // Square wave
    
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResonareAudioProcessor)
};
