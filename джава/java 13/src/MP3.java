public class MP3 implements MediaPlayer {
    String soundName;
    int soundDuration;

    public void play() {
        System.out.println("Воспроизводится '" + soundName + "' длинтельностью " + soundDuration + "с");
    }

    public MP3(String soundName, int soundDuration) {
        this.soundName = soundName;
        this.soundDuration = soundDuration;
    }
}
