<?php

require_once("xml2json/xml2json.php");

define("EXPERIAN_USERNAME", "emerging");
define("EXPERIAN_PASSWORD", "dfgr^e3r9s");


/**
 * Experian Form
 *
 */
function experian_test($form, &$form_state) {
  $form = array();
  
  
  if(!empty($form_state["rebuild"]) && !empty($form_state["values"])) {
    $data = $form_state["values"];
    
    
    if($data["product"] == "criminal") {
      $dob = $data["birthdate"]["year"].$data["birthdate"]["month"].$data["birthdate"]["day"];
      $form = experian_criminal_form($data["first_name"], $data["last_name"], $dob, $data["ssn"]);
    }
    
    if($data["product"] == "civil") {
      $form = experian_civil_form($data["ssn"]);
    }
    
    if($data["product"] == "address") {
      $form = experian_address_form($data["ssn"]);
    }
    
  } else {
  
    $form['first_name'] = array(
  		'#title' => t('First Name'),
  		'#type' => 'textfield'
  	);
  	
  	$form['last_name'] = array(
  		'#title' => t('Last Name'),
  		'#type' => 'textfield'
  	);
  	
  	$form['birthdate'] = array(
  	  '#title' => t('Birthdate'),
  	  '#type' => 'date',
  	  '#description' => t('Select your birthdate'),
  	  '#default_value' => array(
  	  	    'month' => format_date(time(), 'custom', 'n'),
  	  	    'day' => format_date(time(), 'custom', 'j'),
  	  	    'year' => format_date(time(), 'custom', 'Y'),
          )
  	);
  	
  	$form['ssn'] = array(
  		'#title' => t('Social Security Number'),
  		'#type' => 'textfield'
  	);
  	
  	$form['product'] = array(
      '#type'=>'radios',
      '#required' => TRUE,
      '#options'=>array(
        "criminal"=>"Criminal",
        "civil"=>"Civil",
        "address"=>"Address"
      ),
      '#default_value' => 'criminal',
      '#title'=>t('Select Product')
    );
  	
  	$form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit')
    );
  }
  
	return $form;
}

/**
 * 
 */
function experian_test_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Entry point to get Criminal History
 * 
 * @return array a form in the Drupal Form API format
 */
function experian_criminal_form($firstName, $lastName, $dob, $ssn) {
  $form = array();
  
  $history = json_decode(getCriminalHistory($firstName, $lastName, $dob, $ssn), true);
  
  $historyJSON = json_encode($history["Search_results"]["Record"]);
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}

/**
 * Entry point to get Civil History
 * 
 * @return array a form in the Drupal Form API format
 */
function experian_civil_form($ssn) {
  $form = array();
  
  $history = json_decode(getCivilHistory($ssn), true);
  if(!empty($history)) {
    $historyJSON = json_encode($history["xmlgw"]["search_response"]["response_data"]);
  }
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}

/**
 * Entry point to get Address History
 * 
 * @return array a form in the Drupal Form API format
 */
function experian_address_form($ssn) {
  $form = array();

  $history = json_decode(getAddressHistory($ssn), true);
  $historyJSON = json_encode($history["xmlgw"]["search_response"]["response_data"]);
  
  $form['jsonView'] = array(
		'#markup' => _getMarkup($historyJSON)
	);
		
  return $form;
}


function getCriminalHistory($firstName, $lastName, $dateOfBirth, $ssn) {
/* PRODUCTION

  $url = "https://www.appcheckdata.com/ws_criminal3/criminal.svc/xml/ssn?".
  "account=".urlencode(EXPERIAN_USERNAME).
  "&key=".urlencode(EXPERIAN_PASSWORD).
  "&ssn_source=1".
  "&ssn=".urlencode($ssn).
  "&lastname=".urlencode($lastName).
  "&firstname=".urlencode($firstName).
  "&DOB_yyyymmdd=".urlencode($dateOfBirth).
  "&disclaimers_agree=y".
  "&ref=CS";
  
  $xml = file_get_contents($url);
*/  

  $xml = file_get_contents(dirname(__FILE__)."/example_criminal.xml");
  
  return _xmlToJSON($xml);
}

function getCivilHistory($ssn) {
/* PRODUCTION

  $url = "https://www.appcheckdata.com/xmlcivil/index.php".
  "account=".urlencode(EXPERIAN_USERNAME).
  "&key=".urlencode(EXPERIAN_PASSWORD).
  "&ssn=".urlencode($ssn);
  
  $xml = file_get_contents($url);
*/
  
  $xml = file_get_contents(dirname(__FILE__)."/example_civil.xml");

  return _xmlToJSON($xml);
}


function getAddressHistory($ssn) {
  /* PRODUCTION
  
  $postdata = http_build_query(array("request"=> urlencode('<?xml version="1.0"?>
    <xmlgw>
     <session>
          <user_id>'.EXPERIAN_USERNAME.'</user_id>
          <password>'.EXPERIAN_PASSWORD.'</password>
          <customer_reference>Emerging Firms</customer_reference>
     </session>
     <search_request>
          <search>stpeople</search>
          <search_identifier>search-id</search_identifier>
          <search_criteria>
          <ssn>'.$ssn.'</ssn>
          </search_criteria>
     </search_request>
    </xmlgw>')));

  $opts = array('http' =>
      array(
          'method'  => 'POST',
          'header'  => 'Content-type: application/x-www-form-urlencoded',
          'content' => $postdata
      )
  );
  
  $context  = stream_context_create($opts);
  
  $xml = file_get_contents('https://appcheckdata.com/xmlssn/ssntracer_pr.php', false, $context);
  */
  
  $xml = file_get_contents(dirname(__FILE__)."/example_address.xml");  
  
  return _xmlToJSON($xml);
}


function _getMarkup($json = "{}") {
  $markup = "";
  
  if ($path = libraries_get_path("jsonFormat")) {
    // Do something with the library, knowing the path, for instance:
    drupal_add_js($path . '/JSONFormat.js');
    drupal_add_css($path . '/JSONFormat.css');
    
    drupal_add_js(
      "jQuery(document).ready(function () {".
        "window.ImgCollapsed = '".url($path."/images/Collapsed.png")."';".
        "window.ImgExpanded = '".url($path."/images/Expanded.png")."';".
        "Process('".$json."');".
      "});",
      array('type' => 'inline', 'scope' => 'footer')  
    );
    
    $markup = '<div id="jsonView"></div>';
  } else {
    $markup = "COULD NOT FIND jsonFormat Library";
  }
  return $markup;
}


/**
 * Converts XML to JSON
 * @param string xml
 * @return string json string
 */
function _xmlToJSON($xml) {

  $json = xml2json::transformXmlStringToJson($xml);
  return $json;
}