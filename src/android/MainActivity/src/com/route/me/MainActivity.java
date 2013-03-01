package com.route.me;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;  

@SuppressLint("NewApi")
public class MainActivity extends Activity implements LocationListener{
	private TextView latitudeField;
	private TextView longitudeField;
	private LocationManager locationManager;
	private String provider;
	private GoogleMap map;
	static LatLng CurrentyPosition = new LatLng(0, 0);
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        latitudeField = (TextView) findViewById(R.id.TextView02);
        longitudeField = (TextView) findViewById(R.id.TextView04);
        
        //Get the location manager       
        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        
        Criteria criteria = new Criteria();
        provider = locationManager.getBestProvider(criteria, false);
        Location location = locationManager.getLastKnownLocation(provider);        
        Log.v("----------------------------------------------------", location.toString());
        boolean gpsIsEnabled = locationManager.isProviderEnabled(LocationManager.GPS_PROVIDER);
		boolean networkIsEnabled = locationManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER);
		if(gpsIsEnabled){
			locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 500L, 10F, this);
		}else if(networkIsEnabled){
			locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 500L, 10F, this);
		}
		
		onLocationChanged(location);
        
        double lat = location.getLatitude();
        double log = location.getLongitude();
        
        CurrentyPosition= new LatLng(lat, log);
        
        map = ((MapFragment) getFragmentManager().findFragmentById(R.id.map)).getMap();
        map.setMapType(GoogleMap.MAP_TYPE_SATELLITE);
        map.addMarker(new MarkerOptions().position(CurrentyPosition).title("Im Here"));
        
        map.moveCamera(CameraUpdateFactory.newLatLngZoom(CurrentyPosition, 15));
        
        map.animateCamera(CameraUpdateFactory.zoomTo(10), 2000, null);
        map.setMyLocationEnabled(true);
        map.getUiSettings().setMyLocationButtonEnabled(false);
        
    }
	
	 @Override
	  protected void onResume() {
	    super.onResume();	
	    locationManager.requestLocationUpdates(provider, 400, 1, this);
	  }
	 
	 
	 protected void onPause() {
		 super.onPause();
		 locationManager.removeUpdates(this);
	 }
	
	@Override
	public void onLocationChanged(Location location) {
		double lat = (location.getLatitude());
	    double lng = (location.getLongitude());
	    latitudeField.setText(String.valueOf(lat));
	    longitudeField.setText(String.valueOf(lng));
	}

	@Override
	public void onProviderDisabled(String provider) {
		Toast.makeText(this, "Disabled provider " + provider,
		        Toast.LENGTH_SHORT).show();
	}

	@Override
	public void onProviderEnabled(String provider) {
		Toast.makeText(this, "Enabled new provider " + provider,
		        Toast.LENGTH_SHORT).show();
	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		locationManager.requestLocationUpdates(provider, 400, 1, this);	
	}
	
} 