<?php

require_once "classes/KBAWebService.php";

/**
 * Settings
 */
variable_set("rsa_username", "EmergingFirmsINTEG");
variable_set("rsa_password", '$u85ApDR!c2');
variable_set("rsa_ruleset", "customers.emergingfirms.compapp.4quest");
variable_set("rsa_account", "Customers:EmergingFirms:CompanyApp");
variable_set("rsa_state", "testing");
variable_set("rsa_api_trace", 1); // used for debugging


/**
 * Associative array of the form steps
 *
 * @return array form wizard steps
 */
function _kba_steps() {
  return array(
      1 => array(
        'form' => 'kba_personal_info',
      ),
      2 => array(
        'form' => 'kba_questions',
      ),
      3 => array(
        'form' => 'kba_follow_up_question',
      ),
      4 => array(
        'form' => 'kba_follow_up_question_result',
      )
    );
}

/**
 * Entry point to the KBA wizard
 * 
 * @return array a form in the Drupal Form API format
 */
function kba_wizard($form, &$form_state) {

  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;
    
    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = _kba_steps();
  }
  
  $step = &$form_state['step'];
  drupal_set_title(t('Verification: Step @step', array('@step' => $step)));

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);

  // Show the 'previous' button if appropriate. Note that #submit is set to
  // a special submit handler, and that we use #limit_validation_errors to
  // skip all complaints about validation when using the back button. The
  // values entered will be discarded, but they will not be validated, which
  // would be annoying in a "back" button.
  if ($step > 1 && !$form_state['hide_previous_button']) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('kba_wizard_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information']) && !$form_state['hide_next_button']) {
    // The Next button should be included on every step
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('kba_wizard_next_submit'),
    );
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form wizard. Call this button Finish, Submit, or whatever you
    // want to show. When this button is clicked, the
    // kba_wizard_submit handler will be called.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
    );
  }

  // Include each validation function defined for the different steps.
  if (function_exists($form_state['step_information'][$step]['form'] . '_validate')) {
    $form['next']['#validate'] = array($form_state['step_information'][$step]['form'] . '_validate');
  }
  
  // Option to show buttons
  $form_state['hide_next_button'] = false;
  $form_state['hide_previous_button'] = false;
    

  return $form;
}

/**
 * Submit handler for the "previous" button.
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
 *
 * @return array a form in the Drupal Form API format
 */
function kba_wizard_previous_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step > 1) {
    $current_step--;
    $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param $form
 * @param $form_state
 *
 * @return array a form in the Drupal Form API format
 */
function kba_wizard_next_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }
    $form_state['rebuild'] = TRUE;  // Force rebuild with next step.
    return;
  }
}

/**
 * Retrieves the personal information form, to be sent to get the KBA questions
 *
 * @return array a form in the Drupal Form API format
 */
function kba_personal_info($form, &$form_state) {
  global $user;
	$data_nid = $_SESSION['data_form'];
	$node = node_load($data_nid);

	$form['data_person_nid'] = array(
		'#type' => 'hidden',
		'#default_value' => $data_nid,

	);
	$form['suffix'] = array(
		'#title' => t('Suffix'),
		'#type' => 'textfield',
		'#default_value' => $node->field_name_suffix['und'][0]['value'],

	);
	$form['first_name'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
        '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : $node->field_name_first['und'][0]['value']

	);
	$form['middle_name'] = array(
		'#title' => t('Middle Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['middle_name']) ? $form_state['values']['middle_name'] : $node->field_name_middle['und'][0]['value']
	);
	$form['last_name'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : $node->field_name_last['und'][0]['value']

	);
	$form['maiden_name'] = array(
		'#title' => t('Maiden Name'),
		'#type' => 'textfield',
		'#default_value' => $node->field_name_maiden['und'][0]['value'],

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
	$form['gender'] = array(
	  '#title' => t('Gender'),
	  '#type' => 'select',
	  '#description' => t('Select your gender'),
	  '#options' => array('Male' => 'Male', 'Female' => 'Female'),
	  '#default_value' => !empty($form_state['values']['gender']) ? $form_state['values']['gender'] : $node->field_gender['und'][0]['value']
	);

	$form['ssn'] = array(
		'#title' => t('Social Security Number'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['ssn']) ? $form_state['values']['ssn'] : ''
	);

	$form['address'] = array(
    '#type' => 'addressfield',
    '#title' => t('Address'),
    '#required' => TRUE,
    '#default_value' => array('country' => 'US'), // Selects USA by default
    '#description' => "Please enter your address."
  );
		  
	return $form;
}

/**
 * Retrieves the KBA questions
 *
 * @return array a form in the Drupal Form API format
 */
function kba_questions($form, &$form_state) {
  global $user;
  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][1])) {
    
    $personalInformation = $form_state["step_information"][1];
    
    try {
      $response = json_decode(_ws_verification($personalInformation["stored_values"]), true);  
      
      $transationID = $response["transaction-status"]["transaction-id"];
      
      $form['transaction_id'] = array(
    		'#type' => 'hidden',
    		'#default_value' => $transationID,
    
    	);
      
      $questions = $response["questions"]["question"];
      
      if(!empty($questions)) {
      
        $questionSetID = $response["questions"]["question-set-id"];
        
        $form['question_set_id'] = array(
      		'#type' => 'hidden',
      		'#default_value' => $questionSetID,      
      	);
        
        foreach($questions as $question) {
          
          $questionTitle = $question["text"]["statement"];
          $questionID = $question["question-id"];
          $helpText = $question["help-text"]["statement"];
          
          $questionOptions = $question["choice"];
          
          // Form API question options
          $questionFormOptions = array();
          foreach($questionOptions as $questionOption) {
             $questionFormOptions[$questionOption["choice-id"]] = $questionOption["text"]["statement"];
          }
          
          $form["Question_".$questionID] = array(
            '#type'=>'radios',
            '#required' => TRUE,
            '#options'=>$questionFormOptions,
            '#title'=>t($questionTitle),
            '#description'=>t($helpText)
          );
        }
        
      } else {
        
        $form['error'] = array(
          '#markup' => '<div>The Name, DOB, or SSN do not match. Please verify your information is entered correctly. If not, please correct the information and try again. If you feel the information entered is correct, please contact Early IQ <a href="/contact">here</a>.</div>'
        );
        
        // end form
        $form_state['hide_next_button'] = true;
      }
      
    } catch (Exception $e) {
    
        $form['error'] = array(
          '#markup' => '<div>The Name, DOB, or SSN do not match. Please verify your information is entered correctly. If not, please correct the information and try again. If you feel the information entered is correct, please contact Early IQ <a href="/contact">here</a>.</div>'
        );
        
        // end form
        $form_state['hide_next_button'] = true;
    }
  }
  
  return $form;
}

/**
 * Retrieves the follow up question or a you have passed message.
 *
 * @return array a form in the Drupal Form API format
 */
function kba_follow_up_question($form, &$form_state) {

  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][2])) {  
    $answers = $form_state["step_information"][2];
    $response = json_decode(_ws_question_answers($answers["stored_values"]), true);
      
    $question = $response["questions"]["question"];

    // User missed a question, ask the follow up question
    if(!empty($question)) {
      $transationID = $response["transaction-status"]["transaction-id"];
      
      $form['transaction_id'] = array(
    		'#type' => 'hidden',
    		'#default_value' => $transationID,
    
    	);
      
      $questionSetID = $response["questions"]["question-set-id"];
      
      $form['question_set_id'] = array(
    		'#type' => 'hidden',
    		'#default_value' => $questionSetID,      
    	);
        
      $questionTitle = $question["text"]["statement"];
      $questionID = $question["question-id"];
      $helpText = $question["help-text"]["statement"];
      
      $questionOptions = $question["choice"];
      
      // Form API question options
      $questionFormOptions = array();
      foreach($questionOptions as $questionOption) {
         $questionFormOptions[$questionOption["choice-id"]] = $questionOption["text"]["statement"];
      }
      
      $form["Question_".$questionID] = array(
        '#type'=>'radios',
        '#required' => TRUE,
        '#options'=>$questionFormOptions,
        '#title'=>t($questionTitle),
        '#description'=>t($helpText)
      );
        
    } else {
      // User passed the verification
      
      echo "Passed the verification";
      
      // end form wizard
      //$node = node_load($_SESSION['data_form']);

  	  //$node->field_kba['und'][0]['value'] = true;
  	  print_r($form_state['step_information'][1]['stored_values']);
  	  _kba_colect_data($form_state['step_information'][1]['stored_values'],true);
  	  //node_save($node);
  
  	  drupal_goto('node/'.$_SESSION['data_form'].'/edit');
      $form_state["steps"] = 9999;
      
    }
    
    
  }
  return $form;
}

/**
 * Retrieves the result of the KBA
 *
 * @return array a form in the Drupal Form API format
 */
function kba_follow_up_question_result($form, &$form_state) {
  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][3])) {  
    $answers = $form_state["step_information"][3];
    $response = json_decode(_ws_question_answers($answers["stored_values"]), true);
    
    if(!empty($response["information"]["detail-code"]) && $response["information"]["detail-code"] == "passed") {
      echo "You have passed";

      //$node = node_load($_SESSION['data_form']);
      //$node->field_kba['und'][0]['value'] = true;
      print_r($form_state['step_information'][1]['stored_values']);
      _kba_colect_data($form_state['step_information'][1]['stored_values'],true);
	  
      //node_save($node);

      drupal_goto('node/'.$_SESSION['data_form'].'/edit');
    }
    
    _kba_colect_data($form_state['step_information'][1]['stored_values'],false);
  }
  
  return $form;
}


/**
 * Saves the personal information in a node
 *
 * @return null
 */
function _kba_colect_data($data,$kba){

	$node = node_load($_SESSION['data_form']);

	$node->field_name_last['und'][0]['value'] = $data['last_name'];
	$node->field_name_first['und'][0]['value'] = $data['first_name'];
	$node->field_name_maiden['und'][0]['value'] = $data['maiden_name'];
	$node->field_name_middle['und'][0]['value'] = $data['middle_name'];
	$node->field_name_suffix['und'][0]['value'] = $form_state['values']['suffix'];
	$node->field_gender['und'][0]['value'] = $data['gender'];
	$node->field_ssn['und'][0]['value'] = $$data['ssn'];
	$node->field_dob['und'][0]['value'] = $data['birthdate']['year'].'-'.$data['birthdate']['month'].'-'.$data['birthdate']['day'];
	$node->field_address_history['und'][0] = $data['address']['address'];
  $node->field_kba['und'][0]['value'] = $kba;

	node_save($node);
}







/**
 * Wizard form submit handler.
 * - Saves away $form_state['values']
 * - Process all the form values.
 *
 * This demonstration handler just do a drupal_set_message() with the information
 * collected on each different step of the wizard.
 *
 * @param $form
 * @param $form_state
 *
 * @ingroup kb
 */
function kba_wizard_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  // In this case we've completed the final page of the wizard, so process the
  // submitted information.
  foreach ($form_state['step_information'] as $index => $value) {
    // Remove FAPI fields included in the values (form_token, form_id and form_build_id
    // This is not required, you may access the values using $value['stored_values']
    // but I'm removing them to make a more clear representation of the collected
    // information as the complete array will be passed through drupal_set_message().
    unset($value['stored_values']['form_id']);
    unset($value['stored_values']['form_build_id']);
    unset($value['stored_values']['form_token']);
    
  }
}

/**
 * Sends the personal information to the KBA in order to retreive questions
 *
 * @return string the json of the response, or null if empty.
 */
function _ws_verification($data) {
  
  $webService = _createWebService();
  
  $personID   = $data["data_person_nid"];
  $firstName  = $data["first_name"];
  $lastName   = $data["last_name"];
  $email      = $data["email"];
  $ssn        = $data["ssn"];
  $birthYear  = $data["birthdate"]["year"];
  $birthMonth = $data["birthdate"]["month"];
  $birthDay   = $data["birthdate"]["day"];
  
  $address1   = $data["address"]["address"]["thoroughfare"];
  $address2   = $data["address"]["address"]["premise"];
  $addressCity  = $data["address"]["address"]["locality"];
  $addressState = $data["address"]["address"]["administrative_area"];
  $addressZip   = $data["address"]["address"]["postal_code"];
  
  $settings = _getWebServiceSettings();
  $settings["task"] = "iauth"; // adding an additional setting for this specific call
  
  $requestData = array(
      "settings" => $settings,
      "person" => array(
          "name-first" => $firstName,
          "name-last"  => $lastName,
          "email" => $email, // NOT REQUIRED
          "ssn" => $ssn,
          "ssn-type" => "ssn9",
          "birthdate" => array(
              "year" => $birthYear,
              "month" => $birthMonth,
              "day" => $birthDay
          ),
          "address" => array(
              "address-street1" => $address1,
              "address-street2" => $address2,
              "address-city"    => $addressCity,
              "address-state"   => $addressState,
              "address-zip"     => $addressZip,
              "address-context" => "primary"
          )
      ),
      "transaction" => array(
          "account-verification" => array(
              "account-maintenance" => array(
                  "account" => array(
                      "customer-id" => $personID
                  )
              ),
              "venue" => array(
                  "online" => array(
                      "credential" => array(
        				        "credential-method" => "ssn"
                      )
                  )
              ),
              "activity-date" => gmdate("c") // current datetime in GMT and in the ISO 8601 format.
          )
      )
  );
  
  $data = $webService->identityVerification($requestData);
  
  $results = null;
  if(!empty($data) && !empty($data["response"])) {
    $results = json_encode($data["response"]);
  }
    
  return $results;
}

/**
 * Sends the answers to the KBA, retrieves the response in JSON
 * 
 * @return string the json of the response, or null if empty.
 */
function _ws_question_answers($data) {
  
  $webService = _createWebService();
  
  $transactionID = $data["transaction_id"];
  $questionSetID = $data["question_set_id"];
  $answers = array();
  
  foreach($data as $key => $value) {
  
    $key = strtolower($key); // lowercase fieldname
    
    // get the integer from the fieldname
    $questionID = intval(substr($key, 9));
    
    if(!empty($questionID) && is_integer($questionID)) {
      $answers[] = array(
        "question-id" => $questionID,
        "choices" => array(
          "choice-id" => $value
        )
      );
    }
    
  }
  
  $settings = _getWebServiceSettings();
  $settings["transaction-id"] = $transactionID; // adding an additional setting for this specific call
  			
  $requestData = array(
      "settings" => $settings,
      "answers" => array(
          "question-set-id" => $questionSetID,
          "answer"  => $answers
      )
  );
  
  $data = $webService->continuation($requestData);
  
  $results = null;
  if(!empty($data)) {
    $results = json_encode($data);
  }
    
  return $results;
}

/**
 * Creates the KBA webservice with the default settings
 *
 * @return KBAWebService the KBA class
 */
function _createWebService() {
  
  return new KBAWebService(
    array(
      "login" => variable_get("rsa_username"),
      "password" => variable_get("rsa_password"),
      'trace' => variable_get("rsa_api_trace")
    ),
    dirname(__FILE__)."/rsa_kba.wsdl" // real path to the RSA KBA wsdl
  );
}

/**
 * Retrieves the RSA KBA web service settings
 *
 * @return array the default settings for the RSA KBA API
 */
function _getWebServiceSettings() {
  return array(
    "account-name" => variable_get("rsa_account"),
    "mode" => variable_get("rsa_state"),
    "ruleset" => variable_get("rsa_ruleset"),
    
    // Settings for simulated mode
    // "mode" => "simulated",
    // "simulator-mode"=>"questions",

  );
}

