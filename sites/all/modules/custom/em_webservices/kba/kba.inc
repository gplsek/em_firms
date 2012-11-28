<?php

require_once "classes/KBAWebService.php";

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
  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#submit' => array('kba_wizard_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
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

  return $form;
}

/**
 * Submit handler for the "previous" button.
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
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
 *
 */
function kba_personal_info($form, &$form_state) {
  global $user;
  drupal_set_message("HELLO I'M TESTING IT DUDES!!!!!!!!!!!!!!!!!!");
	$form['data_person_nid'] = array(
		'#type' => 'hidden',
		//'#default_value' => $data_nid,

	);
	$form['first_name'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
    '#default_value' => !empty($form_state['values']['first_name']) ? $form_state['values']['first_name'] : ''

	);
	$form['middle_name'] = array(
		'#title' => t('Middle Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['middle_name']) ? $form_state['values']['middle_name'] : ''
	);
	$form['last_name'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
		'#default_value' => !empty($form_state['values']['last_name']) ? $form_state['values']['last_name'] : ''

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
	  '#default_value' => !empty($form_state['values']['gender']) ? $form_state['values']['gender'] : ''
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
 * 
 */
function kba_questions($form, &$form_state) {
  global $user;
  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][1])) {
    
    $personalInformation = $form_state["step_information"][1];
    
    
    //echo json_pretty($response, array("format"=>"html"));
    
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
        echo "COULD NOT FIND QUESTIONS";
      }
      
    } catch (Exception $e) {
        echo 'Caught exception: ',  $e->getMessage(), "\n";
    }
  }
  
  return $form;
}

/**
 * 
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
      
      
    }
    
    
  }
  return $form;
}

function kba_follow_up_question_result($form, &$form_state) {
  $form = array();
  
  if(!empty($form_state["step_information"]) && !empty($form_state["step_information"][3])) {  
    $answers = $form_state["step_information"][3];
    $response = json_decode(_ws_question_answers($answers["stored_values"]), true);
    
    if(!empty($response["information"]["detail-code"]) && $response["information"]["detail-code"] == "passed") {
      echo "You have passed";
    }
  }
  
  return $form;
}


// And now comes the magic of the wizard, the function that should handle all the
// inputs from the user on each different step.
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
  drupal_set_message(t('This information was collected by this wizard:'));
  foreach ($form_state['step_information'] as $index => $value) {
    // Remove FAPI fields included in the values (form_token, form_id and form_build_id
    // This is not required, you may access the values using $value['stored_values']
    // but I'm removing them to make a more clear representation of the collected
    // information as the complete array will be passed through drupal_set_message().
    unset($value['stored_values']['form_id']);
    unset($value['stored_values']['form_build_id']);
    unset($value['stored_values']['form_token']);

    // Now show all the values.
    drupal_set_message(
        t('Step @num collected the following values: <pre>@result</pre>', 
        array('@num' => $index, '@result' => print_r($value['stored_values'], TRUE)))
    );
  }
}


function _ws_verification($data) {
  
  $options = array("login" => "EmergingFirmsINTEG", "password" => '$u85ApDR!c2', 'trace' => 1);
  $webService = new KBAWebService($options, dirname(__FILE__)."/rsa_kba.wsdl");
  
  $personID = $data["data_person_nid"];
  $firstName = $data["first_name"];
  $lastName  = $data["last_name"];
  $email     = $data["email"];
  $ssn       = $data["ssn"];
  $birthYear = $data["birthdate"]["year"];
  $birthMonth = $data["birthdate"]["month"];
  $birthDay = $data["birthdate"]["day"];
  
  $address1 = $data["address"]["address"]["thoroughfare"];
  $address2 = $data["address"]["address"]["premise"];
  $addressCity = $data["address"]["address"]["locality"];
  $addressState = $data["address"]["address"]["administrative_area"];
  $addressZip = $data["address"]["address"]["postal_code"];
  
  
  $requestData = array(
      "settings" => array(
          "account-name" => "Customers:EmergingFirms:CompanyApp",
          "mode" => "testing",
          //"mode" => "simulated", // simulated testing
          //"simulator-mode"=>"questions",
          
          "ruleset" => "customers.emergingfirms.compapp.4quest",
          "task" => "iauth"
      ),
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
                      "customer-id" => "TESTING_".mt_rand(10, 1000000) //$personID
                  )
              ),
              "venue" => array(
                  "online" => array(
                      "credential" => array(
  				        "credential-method" => "ssn"
                      )
                  )
              ),
              "activity-date" => gmdate("c")
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

function _ws_question_answers($data) {
  
  $options = array("login" => "EmergingFirmsINTEG", "password" => '$u85ApDR!c2', 'trace' => 1);
  $webService = new KBAWebService($options, dirname(__FILE__)."/rsa_kba.wsdl");
  
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
  			
  $requestData = array(
      "settings" => array(
          "account-name" => "Customers:EmergingFirms:CompanyApp",
          "mode" => "live",
          "ruleset" => "customers.emergingfirms.compapp.4quest",
          "transaction-id" => $transactionID
      ),
      "answers" => array(
          "question-set-id" => $questionSetID,
          "answer"  => $answers
      )
  );
  
  $data = $webService->continuation($requestData);
  //echo json_pretty(json_encode($data), array("format"=>"html"));
  
  $results = null;
  if(!empty($data)) {
    $results = json_encode($data);
  }
    
  return $results;


}








/**
 * Pretty-print JSON string
 *
 * Use 'format' option to select output format - currently html and txt supported, txt is default
 * Use 'indent' option to override the indentation string set in the format - by default for the 'txt' format it's a tab
 *
 * @param string $json Original JSON string
 * @param array $options Encoding options
 * @return string
 */
function json_pretty($json, $options = array())
{
    $tokens = preg_split('|([\{\}\]\[,])|', $json, -1, PREG_SPLIT_DELIM_CAPTURE);
    $result = '';
    $indent = 0;

    $format = 'txt';

    //$ind = "\t";
    $ind = "    ";

    if (isset($options['format'])) {
        $format = $options['format'];
    }

    switch ($format) {
        case 'html':
            $lineBreak = '<br />';
            $ind = '&nbsp;&nbsp;&nbsp;&nbsp;';
            break;
        default:
        case 'txt':
            $lineBreak = "\n";
            //$ind = "\t";
            $ind = "    ";
            break;
    }

    // override the defined indent setting with the supplied option
    if (isset($options['indent'])) {
        $ind = $options['indent'];
    }

    $inLiteral = false;
    foreach ($tokens as $token) {
        if ($token == '') {
            continue;
        }

        $prefix = str_repeat($ind, $indent);
        if (!$inLiteral && ($token == '{' || $token == '[')) {
            $indent++;
            if (($result != '') && ($result[(strlen($result) - 1)] == $lineBreak)) {
                $result .= $prefix;
            }
            $result .= $token . $lineBreak;
        } elseif (!$inLiteral && ($token == '}' || $token == ']')) {
            $indent--;
            $prefix = str_repeat($ind, $indent);
            $result .= $lineBreak . $prefix . $token;
        } elseif (!$inLiteral && $token == ',') {
            $result .= $token . $lineBreak;
        } else {
            $result .= ( $inLiteral ? '' : $prefix ) . $token;

            // Count # of unescaped double-quotes in token, subtract # of
            // escaped double-quotes and if the result is odd then we are 
            // inside a string literal
            if ((substr_count($token, "\"") - substr_count($token, "\\\"")) % 2 != 0) {
                $inLiteral = !$inLiteral;
            }
        }
    }
    return $result;
}

