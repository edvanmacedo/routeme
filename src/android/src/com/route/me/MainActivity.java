package com.route.me;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

@SuppressLint("NewApi")
public class MainActivity extends Activity {
	static final LatLng MANAUS = new LatLng(-3.105549,-60.02655);
	static final LatLng RIOPRETO = new LatLng(-2.698699,-59.700737);
	private GoogleMap map;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);      
        
        map = ((MapFragment) getFragmentManager().findFragmentById(R.id.map)).getMap();    
        map.setMapType(GoogleMap.MAP_TYPE_SATELLITE);
        map.addMarker(new MarkerOptions().position(MANAUS).title("MANAUS"));
        map.addMarker(new MarkerOptions().position(RIOPRETO).title("Rio Preto").snippet("Rio preto da eva tem nada").icon(BitmapDescriptorFactory.fromResource(R.drawable.ic_launcher)));

        // Move the camera instantly to hamburg with a zoom of 15.
        map.moveCamera(CameraUpdateFactory.newLatLngZoom(MANAUS, 15));

        // Zoom in, animating the camera.
        map.animateCamera(CameraUpdateFactory.zoomTo(10), 2000, null);
        
    }

} 