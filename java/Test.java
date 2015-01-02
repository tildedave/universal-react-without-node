import java.lang.System;

public class Test {
        static {
                System.loadLibrary("react_render");
        }

        public static void main(String[] args) {
                System.out.println("Hello, JAva!");

                react_render.set_debug(1);
                react_render.initialize("../bundle.js");
                react_render.render_element("Homepage");
        }
}
