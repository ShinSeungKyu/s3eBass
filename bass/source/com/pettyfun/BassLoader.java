package com.pettyfun;

import com.ideaworks3d.marmalade.LoaderActivity;

public class BassLoader extends LoaderActivity {

    static {
        System.loadLibrary("bass");
    }

}
