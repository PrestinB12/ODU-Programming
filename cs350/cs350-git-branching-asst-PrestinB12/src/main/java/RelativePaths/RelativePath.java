/**
 * 
 */
package RelativePaths;

import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Utility to find relative paths from one file location to another.
 * 
 * @author zeil
 *
 */
public class RelativePath {
	public Path workingDirectory;
	public Path target;
	
	/**
	 * Create a relative path object describing how to get from
	 * workingDir to aTarget.
	 *  
	 * @param workingDir  the working directory, a starting point in a file system.
	 * @param aTarget the desired file that we want to access usign a relative path.
	 */
	public RelativePath (String workingDir, String aTarget) {
		workingDirectory = Paths.get(workingDir).normalize();
		target = Paths.get(aTarget).normalize();
	}
	
	/**
	 * Get the relative path the from the working directory to the target.
	 * @return the relative path.
	 */
	public String getRelative() {
		return workingDirectory.relativize(target).toString();
	}
	
	/**
	 * Printable summary of this object, for debugging purposes.
	 */
	public String toString() {
		return "To get from " + workingDirectory.toString() + " to "
				+ target.toString() + ", follow " + getRelative();
	}
}
