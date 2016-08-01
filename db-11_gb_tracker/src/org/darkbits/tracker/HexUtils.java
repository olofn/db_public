package org.darkbits.tracker;

public class HexUtils {
	private HexUtils() {};
	
	public static String toHex(int v, int length) {
		String h = Integer.toHexString(v);
		
		while (h.length() < length) {
			h = "0" + h;
		}

		return h.toUpperCase();
	}
}
