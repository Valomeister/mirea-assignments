public class Main {
    public static void main(String[] args) {
        MP3 MP3_TRACK = new MP3("Трек №13", 54);
        WAV WAV_TRACK = new Mp3ToWavAdapter(MP3_TRACK);
        WAV_TRACK.connectWAV();
    }
}
