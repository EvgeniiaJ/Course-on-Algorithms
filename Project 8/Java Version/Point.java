public class Point {
	
	private double xCoordinate;
	private double yCoordinate;
	private int label;
	private double distance;
	
	public Point() {
		this.xCoordinate = 0.0;
		this.yCoordinate = 0.0;
		this.label = 0;
		this.distance = 99999.0;
	}
	
	public Point(double xCoordinate, double yCoordinate, int label, double distance) {
		this.xCoordinate = xCoordinate;
		this.yCoordinate = yCoordinate;
		this.label = label;
		this.distance = distance;
	}

	public double getXCoordinate() {
		return xCoordinate;
	}

	public void setXCoordinate(double xCoordinate) {
		this.xCoordinate = xCoordinate;
	}

	public double getYCoordinate() {
		return yCoordinate;
	}

	public void setYCoordinate(double yCoordinate) {
		this.yCoordinate = yCoordinate;
	}

	public int getLabel() {
		return label;
	}

	public void setLabel(int label) {
		this.label = label;
	}

	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}

}
