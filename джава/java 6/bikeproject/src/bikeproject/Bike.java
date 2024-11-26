package bikeproject;

public class Bike implements Defaults, BikeParts{

	private String handleBars, frame, tyres, seatType;
	private int NumGears;

	public String getHandleBars() {
		return handleBars;
	}

	public void setHandleBars(String handleBars) {
		this.handleBars = handleBars;
	}

	public String getFrame() {
		return frame;
	}

	public void setFrame(String frame) {
		this.frame = frame;
	}

	public String getTyres() {
		return tyres;
	}

	public void setTyres(String tyres) {
		this.tyres = tyres;
	}

	public String getSeatType() {
		return seatType;
	}

	public void setSeatType(String seatType) {
		this.seatType = seatType;
	}

	public int getNumGears() {
		return NumGears;
	}

	public void setNumGears(int numGears) {
		this.NumGears = numGears;
	}

	public Bike(){}//end constructor

	public Bike(String handleBars, String frame, String tyres, String seatType, int numGears) {
		this.handleBars = handleBars;
		this.frame = frame;
		this.tyres = tyres;
		this.seatType = seatType;
		this.NumGears = numGears;
	}//end constructor

	@Override
	public void printDescription()
	{
		System.out.println("\n" + this.make + "\n" 
				          + "This bike has " + this.handleBars + " handlebars on a " 
				          + this.frame + " frame with " + this.NumGears + " gears."  
				          + "\nIt has a " + this.seatType + " seat with " + this.tyres + " tyres.");
	}//end method printDescription

}//end class Bike
	
	

