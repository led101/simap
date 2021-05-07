import pyaudio
import numpy as np
import wave

p = pyaudio.PyAudio()

volume = 1     # range [0.0, 1.0]
fs = 44100       # sampling rate, Hz, must be integer
duration = 1.0   # in seconds, may be float
f = 440        # sine frequency, Hz, may be float

# generate samples, note conversion to float32 array
samples = (np.sin(2*np.pi*np.arange(fs*duration)*f/fs)).astype(np.float32)
samples2 = (np.sin(2*np.pi*np.arange(fs*duration)*(f*7/4)/fs)).astype(np.float32)
samples3 = samples + samples2

# for paFloat32 sample values must be in range [-1.0, 1.0]
stream = p.open(format=pyaudio.paFloat32,
                channels=1,
                rate=fs,
                output=True)

# play. May repeat with different volume values (if done interactively) 
#stream.write(volume*samples)
stream.write(0.3*samples2 + 0.1*samples)



frames = []  # Initialize array to store frames

# Store data in chunks for 3 seconds
for i in range(0, int(      )):
    data = stream.read(0.3samples2 + 0.1samples)
    frames.append(data)


# 
stream.stop_stream()
stream.close()
p.terminate()

wf = wave.open("trial.wav", 'wb')
wf.setnchannels(1)
wf.setsampwidth(p.get_sample_size(sample_format))
wf.setframerate(fs)
wf.writeframes(b''.join(frames))
wf.close()