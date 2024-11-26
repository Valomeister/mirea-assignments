package bikeproject;

public interface BikeParts {
    String getHandleBars();
    String getFrame();
    String getTyres();
    String getSeatType();
    int getNumGears();
    void setHandleBars(String handleBars);
    void setFrame(String frame);
    void setTyres(String tyres);
    void setSeatType(String seatType);
    void setNumGears(int numGears);
}
