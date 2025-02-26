/**
 * 
 */

package RelativePaths;

import java.io.File;

import javax.swing.JFileChooser;

/**
 * @author zeil
 *
 */
public class ShowRelative {

	/**
	 * Prompt the user to provide a pair of paths and prints the
	 * relative path from the first to the second.
	 * 
	 * @param args ignored
	 */
	public static void main(String[] args) {
		final JFileChooser wdChooser = new JFileChooser();
		wdChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		wdChooser.setDialogTitle("Choose a working directory");
		int status = wdChooser.showOpenDialog(null);
		if (status != 0) {
			System.err.println ("Canceled");
			System.exit(1);
		}
		File workingDir = wdChooser.getSelectedFile();
		
		wdChooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
		wdChooser.setDialogTitle("Choose a target file or directory");
		status = wdChooser.showOpenDialog(null);
		if (status != 0) {
			System.err.println ("Canceled");
			System.exit(1);
		}
		File target = wdChooser.getSelectedFile();
		RelativePath rp = new RelativePath(workingDir.toString(), target.toString());
		System.out.println(rp.toString());
	}

}
