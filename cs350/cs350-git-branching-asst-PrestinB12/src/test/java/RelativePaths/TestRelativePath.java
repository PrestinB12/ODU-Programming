package RelativePaths;

import static org.junit.jupiter.api.Assertions.*;

import java.io.File;

import org.junit.jupiter.api.Test;


public class TestRelativePath {

	@Test
	public void testRelativePathUp() {
		RelativePath rp = new RelativePath("/home/jdoe/bin", "/home/jdoe");
		assertEquals ("..", rp.getRelative());
	}

	@Test
	public void testRelativePathDown() {
		RelativePath rp = new RelativePath("/home/jdoe/bin", "/home/jdoe/bin/progs/prog0.in");
		String expected = "progs/prog0.in".replace('/', File.separatorChar);
		assertEquals (expected, rp.getRelative());
	}

	@Test
	public void testRelativePathOver() {
		RelativePath rp = new RelativePath("/home/jdoe/bin", "/home/asmith/bin/prog0.in");
        String expected = "../../asmith/bin/prog0.in".replace('/', File.separatorChar);
		assertEquals (expected, rp.getRelative());
	}
	
}
