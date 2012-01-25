<?php

/**
 * @file
 * Home of the FeedsSunlightFetcher and related classes.
 */

/**
 * Result of FeedsSunlightFetcher::fetch().
 */
class FeedsSunlightFetcherResult extends FeedsFetcherResult {
	
  protected $class;
  protected $filters = array();
  
  /**
   * Constructor.
   */
  public function __construct($class = FEEDS_SUNLIGHT_DEFAULT_ENTITY, $filters = array()) {
    $this->class = $class;
    
    if (is_array($filters)) {
    	$this->filters = $filters;
    }
    
    parent::__construct('');
  }

  /**
   * Overrides FeedsFetcherResult::getRaw();
   */
  public function getRaw() {
  	$connector = feeds_sunlight_get_connector($this->class);
  	
  	try {
  		switch ($this->class) {
  			/*case FEEDS_SUNLIGHT_COMMITTEE:
  				if (!$this->filters) {
  					// Can be; 'House', 'Senate', 'Joint'
  					$this->filters = 'House';
  				}
  				$data = $connector->committeesList($this->filters); // @TODO: Implement a chamber filter.
  				break;
  				
  			case FEEDS_SUNLIGHT_LOBBYIST:
  				if (!$this->filters) {
  					// Search term, then year
  					$search_term = ($this->filters['term'] ? $this->filters['term'] : '');
  					$search_year = ($this->filters['year'] ? $this->filters['year'] : date('Y'));
  				}
  				$data = $connector->lobbyistSearch($search_term, $search_year); // @TODO: Implement proper search filter.
  				break;*/

  			case FEEDS_SUNLIGHT_LEGISLATOR:
  			default:
  				$data = $connector->legislatorList($this->filters); // @TODO: Implement some filters.
  		}
  	}
  	catch (Exception $e) {
  		throw new Exception(t('Download of @class failed with !error.', array('@class' => $this->class, '!error' => $e->getMessage())));
  	} 	
    
    return $data;
  }
}

/**
 * Fetches data via Sunlight Labs Congressional API.
 */
class FeedsSunlightFetcher extends FeedsFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    return new FeedsSunlightFetcherResult($this->config['class'], $source_config['_filters']);
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
    	'class' => FEEDS_SUNLIGHT_DEFAULT_ENTITY,  
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    
    $class_options = array(
    	FEEDS_SUNLIGHT_LEGISLATOR => t('Legislators'),
    	//FEEDS_SUNLIGHT_COMMITTEE  => t('Committees'),
    	//FEEDS_SUNLIGHT_LOBBYIST   => t('Lobbyists'),
    );
    
    $form['class'] = array(
      '#type' => 'radios',
      '#title' => t('Congressional entity type'),
      '#default_value' => $this->config['class'],
      '#options' => $class_options,
    );
    
    return $form;
  }

  /**
   * Expose source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    
    $form['chamber'] = array(
      '#type' => 'select',
      '#title' => t('Congressional chamber'),
      '#default_value' => '__all__',
    	'#options' => array('__all__' => t('All'), 'Rep' => t('House'), 'Sen' => t('Senate')),
    );
    
    // @TODO: Support some configuration options.
    return $form;
  }

  /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {
  	$values['_filters'] = array();
  	
  	// Congressional chamber source filter.
  	if (in_array($values['chamber'], array('Rep', 'Sen'))) {
  		$values['_filters']['title'] = $values['chamber'];
  	}    
  }
}
