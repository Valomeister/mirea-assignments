public class Mp3ToWavAdapter implements WAV {
    private MP3 sound;

    public Mp3ToWavAdapter(MP3 sound) {
        this.sound = sound;
    }

    public void connectWAV() {
        System.out.println("Adapter converts MP3 to WAV");
        sound.play();
    }
}
